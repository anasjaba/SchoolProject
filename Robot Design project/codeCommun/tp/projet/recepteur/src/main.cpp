/**
 * @author Louis Racicot & Samuel Rondeau & Feriel Charfeddine & Liang Weiwei
 * @created: 2014-11-28
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../libpout/src/led.h"
#include "../../libpout/src/sleep.h"
#include "../../libpout/src/memoire_24.h"
#include "../../libpout/src/lcd.h"
#include "../../libpout/src/codeBarre.h"
#include "MoteurManager.h"
#include "RobotManager.h"
#include "Piezoelectrique.h"
using namespace libpout;

enum States {
    AVANCER,                // le robot avance
    DETECT,                 // détection de données (détecteur de poteau / mémoire)
    ADJUST_INTER_DETOUR,    // ajuste les roues au centre de l'intersection lors du détour
    TURN_DETOUR,            // tourne pour effectuer le détour
    DETOUR,                 // effectue le trajet vers la ligne D
    UTURN,                  // u-turn une fois arrivé au bout
    SHUTDOWN,               // attente jusqu'au reset
    ADJUST_INTER_NEW_LINE,  // ajuste les roues au centre de l'intersection à une ligne principale
    ADJUST_INTER_RETOUR,    // ajuste les roues au centre de l'intersection au retour
    TURN_NEW_LINE,          // tourne sur une nouvelle ligne principale
    TURN_RETOUR,            // tourne pour effectuer son retour vers C
    RETOUR,                 // effectue le trajet vers la ligne C
    INITIAL,                // état initial en attente d'instruction par infrarouge ou code à barres
    DETECT_NEW_LINE         // détecte un poteau pour savoir si le robot reste sur la nouvelle ligne ou non
};

enum Line {
    LIGNE_C,
    LIGNE_D
};

volatile bool reverse = false;          // false = aller; true = retour
volatile bool pressed = false;          // true = le bouton interrupt est appuyé et maintenu
volatile uint8_t obstacles = 0x00;      // position des obstacles (bits à 1)
volatile uint8_t dataReceived = 0x00;   // chaque bit à 1 est une donnée reçue
uint8_t waitingData = 0;                // quelle donnée (bit) est en attente
uint8_t vitesse = 120;                  // vitesse du robot
uint8_t position = 0;                   // position actuelle du robot
States state;                           // état actuel
Line line;                              // ligne actuelle

RobotManager* robot_;                   // gestionnaire des actions du robot
MoteurManager* engines_;                // gestionnaire des moteurs
Recepteur recepteur;                    // récepteur infrarouge

/*
*  Gère les interruptions de l'infrarouge
*/
ISR (INT2_vect) {
    if (PINB == 0x00) {
        _delay_loop_1(1);
        recepteur.ISR_INT_vect();
    }

    // Si le signal d'interruption arrive durant l'exécution de ISR, l'AVR s'en souvient
    EIFR |= (1 << INTF0);
}

/*
*  Gère les interruptions sur le timer de lecture d'IR
*/
ISR (TIMER2_COMPA_vect) {
    recepteur.ISR_TIMER_COMP_vect();
    if (recepteur.isDataReady()) {
        uint8_t data = recepteur.getData();

        obstacles |= data << waitingData;
        dataReceived |= 1 << waitingData;
    }
}

/*
*  Détermine si le bouton interrupt est appuyé (et maintenu)
*/
bool isClicked() {
    // Vérifier si on appuie sur le bouton poussoir
    if (PIND & 0x04) {
        _delay_ms(30);  // Attendre 10ms pour éviter le rebond

        if (PIND & 0x04)
            return true;
    }

    return false;
}

/*
*  Gère les interruptions sur le bouton poussoir interrupt.
*  Utilisé lors du retour
*/
ISR (INT0_vect) {
    // Laisser un delai avant de confirmer la reponse du bouton poussoir
    _delay_loop_2 (65530);
    
    if (isClicked()) {
        PORTB |= 0x01;
        pressed = true;
    }
    else {
        PORTB &= ~(0x01);
        pressed = false;
        reverse = true;
    }

    // Si le signal d'interruption arrive durant l'exécution de ISR, l'AVR s'en souvient
    EIFR |= (1 << INTF0);      
}

/*
*  Initialise les ports et registres
*/
void init() {
    cli();

    DDRA = 0x00;    // 0x0x0xx0 // A0 = lecteur code barres
                                // A3, A5, A7 = détecteur de ligne où A3 = gauche à A7 = droite
    DDRB = 0x2B;    // xx1x1011 // B[1:0] = DEL libre
                                // B2 = IR
                                // B3 et B5 = piézoélectrique
                                // B[7:4] = make install
    DDRC = 0xFF;    // 11111111 // C[7:0] = LCD
    DDRD = 0x38;    // xx1110xx // D2 = INT0 (interrupt) [initial]
    //DDRD = 0x3C;  // xx1111xx // D2 = direction gauche [later]
                                // D3 = direction droite
                                // D4 = PWM gauche
                                // D5 = PWM droit

    // Permettre les interruptions externes
    EIMSK |= _BV(INT2);
    EIMSK |= _BV(INT0);

    // Sensibiliser les interruptions externes
    EICRA |= _BV(ISC20); // Any edge
    EICRA |= _BV(ISC01) | _BV(ISC00);

    sei();
}

/*
*  Gère le changement d'état du robot
*/
void changeState(States newState) {
    state = newState;
}

/*
*  Détermine si une coordonnée contient un obstacle en modes aller et retour
*/
bool thereIsObstacle(uint8_t coord) {
    if (reverse) {
        return coord < 7 && (obstacles >> (7-coord)) & 0x01;
    }
    else {
        return (obstacles >> coord) & 0x01;
    }
}

/*
*  Détermine si une coordonnée contient un obstacle en modes aller et retour
*/
bool isDataReceived(uint8_t coord) {
    waitingData = coord;
    if (reverse) {
        return true;
    }
    else {
        return dataReceived >> coord;
    }
}

/*
*  Tourne pour effectuer un détour à partir de la ligne C en modes aller et retour
*/
void turnDetourC() {
    if (reverse) {
        robot_->turnLeft90();
    }
    else {
        robot_->turnRight90();
    }
}

/*
*  Tourne pour effectuer un retour à partir de la ligne D en modes aller et retour
*/
void turnRetourD() {
    if (reverse) {
        robot_->turnRight90();
    }
    else {
        robot_->turnLeft90();
    }
}


/*
*  Tourne pour se rendre vers une nouvelle ligne à partir de la ligne C en modes aller et retour
*/
void turnNewLineC() {
    if (reverse) {
        robot_->turnRight90();
    }
    else {
        robot_->turnLeft90();
    }
}

/*
*  Tourne pour se rendre vers une nouvelle ligne à partir de la ligne D en modes aller et retour
*/
void turnNewLineD() {
    if (reverse) {
        robot_->turnLeft90();
    }
    else {
        robot_->turnRight90();
    }
}

/*
*  Fonction principale exécutant la logique
*/
int main() {
    init();
    RobotManager robot = RobotManager();
    MoteurManager engines = MoteurManager();
    Memoire24CXXX mem = Memoire24CXXX();

    engines_ = &engines;
    robot_ = &robot;

    changeState(INITIAL);
    line = LIGNE_C;
    
    for(;;) {
        if (line == LIGNE_C) {

            switch (state) {
                case AVANCER:

                    // Following
                    robot.followLine();
                    _delay_ms(250);

                    // Lorsqu'arrivé à une intersection
                    if (robot.intersectionDetected()) {
                        position++;

                        // Si pas à la fin
                        if (position < 7) {
                            changeState(DETECT);
                        }
                        // Si à la fin
                        else {
                            changeState(UTURN);
                        }
                    }

                    break;

                case DETECT:
                    engines.arreter();
                    msleep(100);
                    // Si on a reçu une donnée à la prochaine intersection
                    if (isDataReceived(position + 1)) {
                        msleep(750);
                        // S'il y a un obstacle à la prochaine intersection
                        if (thereIsObstacle(position + 1)) {
                            changeState(ADJUST_INTER_DETOUR); // Tourner
                        }
                        else {
                            robot.followLine();
                            _delay_ms(300);
                            changeState(AVANCER); // Sinon continuer
                        }
                    }
                    // Si aucune donnée reçue, attendre instruction

                    break;
              
                case ADJUST_INTER_DETOUR:
                    robot.adjustIntersection();
                    changeState(TURN_DETOUR);

                    break;
              
                case ADJUST_INTER_NEW_LINE:
                    robot.adjustIntersection();
                    changeState(TURN_NEW_LINE);

                    break;

                case TURN_DETOUR:
                    turnDetourC();
                    changeState(DETOUR);

                    break;

                case TURN_NEW_LINE:
                    turnNewLineC();
                    line = LIGNE_D;
                    changeState(AVANCER);

                    break;

                case DETOUR:
                    // Following
                    robot.followLine();
                    if (robot.intersectionDetected()) {
                        changeState(ADJUST_INTER_NEW_LINE);
                    }

                    break;

                case UTURN:
                    robot.adjustIntersection();
                    robot.turn180();
                    changeState(SHUTDOWN);

                    break;

                case SHUTDOWN:
                    engines.arreter();
                    for(;;);
                    break;

                case INITIAL:
                    uint8_t barreObstacle;
                    // Tant qu'aucune donnée n'est reçue,
                    // attendre une donnée IR ou code barres
                    while (dataReceived == 0x00) {
                        barreObstacle = lireCodeBarre();
                        // Si une donnée est reçue par code barres
                        if (barreObstacle != 0) {
                            dataReceived = 0xFF;
                            obstacles = barreObstacle;
                            robot.jouerSon();
                            // Attendre d'être officiellement en mode retour
                            while (!reverse);

                            EICRA &= ~(_BV(ISC00)); // Désactiver les interruptions
                            DDRD = 0x3C;            // Réactiver la broche du moteur
                            msleep(1000);           // Attendre 1 seconde
                        }
                        // Sinon, une donnée est reçue par infrarouge
                    }
                    changeState(DETECT);

                    break;

                default:
                    changeState(DETECT);

                    break;
            }

        }

        else if (line == LIGNE_D) {

            switch (state) {
                case AVANCER:
                    // Following
                    robot.followLine();
                    // Si une intersection est détectée et que nous ne savons pas s'il y a un obstacle
                    if (robot.intersectionDetected()) {
                        position++;

                        // S'il n'y a pas d'obstacle sur Cx
                        if (!thereIsObstacle(position)) {
                            changeState(DETECT);
                        }
                        else {
                            // Dépasser l'intersection
                            _delay_ms(500);
                        }
                    }

                    break;

                case DETECT:
                    engines.arreter();
                    msleep(100);
                    // Si une donnée est reçue
                    if (isDataReceived(position)) {
                        // S'il y a un obstacle sur Cx
                        if (thereIsObstacle(position)) {
                            changeState(AVANCER);   //Sinon continuer

                        }
                        // S'il n'y a pas d'obstacle sur Cx
                        else {
                            robot.followLine();
                            _delay_ms(300);
                            changeState(ADJUST_INTER_RETOUR);   // Tourner
                        }
                    }

                    break;

                case DETECT_NEW_LINE:
                    engines.arreter();
                    msleep(100);
                    // Si une donnée est reçue
                    if (isDataReceived(position + 1)) {
                        // S'il y a un obstacle sur Cx
                        if (thereIsObstacle(position + 1)) {
                            line = LIGNE_C;
                            changeState(TURN_DETOUR );  // Tourner

                        }
                        // S'il n'y a pas d'obstacle sur Cx
                        else {
                            robot.followLine();
                            _delay_ms(300);
                            line = LIGNE_C;
                            changeState(AVANCER);   // Sinon continuer
                        }
                    }

                    break;
              
                case ADJUST_INTER_RETOUR:
                    robot.adjustIntersection();
                    changeState(TURN_RETOUR);

                    break;
              
                case ADJUST_INTER_NEW_LINE:
                    robot.adjustIntersection();
                    changeState(TURN_NEW_LINE);

                    break;

                case TURN_NEW_LINE:
                    turnNewLineD();
                    changeState(DETECT_NEW_LINE);

                    break;

                case TURN_RETOUR:
                    turnRetourD();
                    changeState(RETOUR);

                    break;

                case RETOUR:
                    // Following
                    robot.followLine();
                    // À une intersection
                    if (robot.intersectionDetected()) {
                        if (position == 7) {
                            robot_->turnLeft90();
                            changeState(SHUTDOWN);
                        }
                        else {
                            changeState(ADJUST_INTER_NEW_LINE);
                        }
                    }

                    break;

                default:
                    changeState(DETECT);

                    break;
            }
        }
    }

    return 0; 
}
