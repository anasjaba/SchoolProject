/**
 * @author Louis Racicot & Samuel Rondeau & Feriel Charfeddine & Liang Weiwei
 * @created: 2014-11-28
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../../libpout/src/sleep.h"
#include "../../libpout/src/memoire_24.h"
#include "MoteurManager.h"
#include "RobotManager.h"
using namespace libpout;

enum States {
    AVANCER,                // le robot avance
    DETECT,                 // détection de données (détecteur de poteau / mémoire)
    ADJUST_INTER_DETOUR,    // ajuste les roues au centre de l'intersection lors du détour
    TURN_DETOUR,            // tourne pour effectuer le détour
    DETOUR,                 // effectue le trajet vers la ligne B
    SAVE,                   // enregistrement en mémoire
    UTURN,                  // u-turn une fois arrivé au bout
    SHUTDOWN,               // attente jusqu'au reset
    ADJUST_INTER_NEW_LINE,  // ajuste les roues au centre de l'intersection à une ligne principale
    ADJUST_INTER_DETECT,    // le robot avance un peu après une intersection pour détecter
    TURN_SEND,              // le robot se positionne pour émettre par IR
    TURN_NEW_LINE,          // tourne sur une nouvelle ligne principale
    TURN_DETECT,            // le robot se retourne pour détecter
    TURN_RETOUR,            // tourne pour effectuer son retour vers A
    RETOUR,                 // effectue le trajet vers la ligne A
    SEND_DATA,              // émission IR des poteaux
    DETECT_NEW_LINE,        // détecte un poteau pour savoir si le robot reste sur la nouvelle ligne ou non
    SEND_DATA_NEW_LINE      // émission IR du choix de la ligne
};

enum Line {
    LIGNE_A,
    LIGNE_B
};

volatile bool reverse = false;  // false = aller; true = retour
volatile bool pressed = false;  // true = le bouton interrupt est appuyé et maintenu
uint8_t vitesse = 120;          // vitesse du robot
uint8_t position = 0;           // position actuelle du robot
uint8_t obstacles = 0x0;        // position des obstacles (bits à 1)
States state;                   // état actuel
Line line;                      // ligne actuelle

RobotManager* robot_;           // gestionnaire des actions du robot
MoteurManager* engines_;        // gestionnaire des moteurs

/*
*  Détermine si le bouton interrupt est appuyé (et maintenu)
*/
bool isClicked() {
    // Vérifier si on appuie sur le bouton poussoir
    if (PIND & 0x04) {
        _delay_ms(10);  // Attendre 10ms pour éviter le rebond

        if (PIND & 0x04) {
            return true;
        }
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
        pressed = true;
        reverse = true;
        PORTA |= 0x02;
    }
    else {
        pressed = false;
        PORTA &= ~(0x02);
    }

    // Si le signal d'interruption arrive durant l'exécution de ISR, l'AVR s'en souvient
    EIFR |= (1 << INTF0);      
}


/*
*  Initialise les ports et registres
*/
void init() {
    cli();

    DDRA = 0x0A;    // xxxxxxx0 // A0 = détecteur de distance
    DDRB = 0x28;    // xx1x1xxx // B3 et B5 = piézoélectrique
                                // B[7:4] = make install
    DDRC = 0x00;    // xx000000 // C[5:0] = détecteur de ligne où C0 = gauche à C4 = droite
    DDRD = 0xF8;    // 111110xx // D2 = INT0 (interrupt)
                                // D3 = direction droite
                                // D4 = PWM gauche
                                // D5 = PWM droit
    PORTD &= 0xBF;              // D6 = 0 (IR)
                                // D7 = IR
    
    // Cette procédure ajuste le registre EIMSK
    // du ATmega324PA pour permettre les interruptions externes
    EIMSK |= _BV(INT0);
    
    // Il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
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
        return robot_->detectPoteau();
    }
}

/*
*  Tourne pour effectuer un détour à partir de la ligne A en modes aller et retour
*/
void turnDetourA() {
    if (reverse) {
        robot_->turnLeft90();
    }
    else {
        robot_->turnRight90();
    }
}

/*
*  Tourne pour effectuer un retour à partir de la ligne B en modes aller et retour
*/
void turnRetourB() {
    if (reverse) {
        robot_->turnRight90();
    }
    else {
        robot_->turnLeft90();
    }
}

/*
*  Tourne pour se rendre vers une nouvelle ligne à partir de la ligne A en modes aller et retour
*/
void turnNewLineA() {
    if (reverse) {
        robot_->turnRight90();
    }
    else {
        robot_->turnLeft90();
    }
}

/*
*  Tourne pour se rendre vers une nouvelle ligne à partir de la ligne B en modes aller et retour
*/
void turnNewLineB() {
    if (reverse) {
        robot_->turnLeft90();
    }
    else {
        robot_->turnRight90();
    }
}

/*
*  Tourne pour détecter un poteau à partir de la ligne B en mode aller
*/
void turnDetectB() {
    if (!reverse) {
        robot_->turnLeft90();
        engines_->tournerGauche(10);
    }
}

/*
*  Tourne pour émettre à partir de la ligne B en mode aller
*/
void turnSendB() {
    if (!reverse) {
        robot_->turnRight90();
    }
}

/*
 *  Fonction principale exécutant la logique
 */
int main() {
    init();
    msleep(2000);
    // On a 2 secondes pour apputer sur le bouton-poussoir en mode retour
    while(pressed == true) {}

    EICRA &= ~(_BV(ISC00)); // Désactiver les interruptions
    DDRD = 0xFC;            // Réactiver la broche du moteur

    RobotManager robot = RobotManager();
    MoteurManager engines = MoteurManager();
    Memoire24CXXX mem = Memoire24CXXX();

    // En mode retour : lecture en mémoire des obstacles
    if (reverse) {
        uint8_t reading[1];
        mem.lecture(0, reading, 1);
        obstacles = reading[0];
    }

    engines_ = &engines;
    robot_ = &robot;

    changeState(DETECT);
    line = LIGNE_A;

    for(;;) {
        if (line == LIGNE_A) {

            switch (state) {
                case AVANCER:
                    // Following
                    robot.followLine();

                    // Lorsqu'arrivé à une intersection
                    if (robot.intersectionDetected()) {
                        position++;

                        // Si pas à la fin
                        if (position < 7) {
                            robot.followLine(2);
                            changeState(DETECT);
                        }
                        // Si à la fin
                        else {
                            robot.followLine(2);
                            changeState(SAVE);
                        }
                    }

                    break;

                case DETECT:
                    engines.arreter();
                    msleep(500);
                    // S'il y a un obstacle à la prochaine intersection
                    if (thereIsObstacle(position + 1)) {
                        obstacles |= 1 << (position + 1);
                        robot.emettre(1);
                        changeState(ADJUST_INTER_DETOUR); // Tourner
                    }
                    else {
                        robot.emettre(0);
                        robot.followLine();
                        _delay_ms(300);
                        changeState(AVANCER); // Sinon continuer
                    }

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
                    turnDetourA();
                    changeState(DETOUR);

                    break;

                case TURN_NEW_LINE:
                    turnNewLineA();
                    line = LIGNE_B;
                    changeState(AVANCER);

                    break;

                case DETOUR:
                    // Following
                    robot.followLine();
                    if (robot.intersectionDetected()) {
                        changeState(ADJUST_INTER_NEW_LINE);
                    }

                    break;

                case SAVE:
                    engines.arreter();
                    mem.ecriture(0, obstacles);
                    changeState(UTURN);

                    break;

                case UTURN:
                    robot.adjustIntersection();
                    robot.turn180();
                    changeState(SHUTDOWN);

                    break;

                case SHUTDOWN:
                    for(;;);
                    break;

                default:
                    changeState(DETECT);

                    break;
            }

        }

        else if (line == LIGNE_B) {

            switch (state) {
                case AVANCER:
                    // Following
                    robot.followLine();
                    // Si une intersection est détectée et que nous ne savons pas s'il y a un obstacle
                    if (robot.intersectionDetected()) {
                        position++;
                        uint8_t obstacle = obstacles >> position;

                        // En mode retour
                        if (reverse) {
                            obstacle = thereIsObstacle(position);
                        }

                        // S'il n'y a pas d'obstacle sur Ax
                        if (!obstacle) {
                            engines.arreter();
                            _delay_ms(400);

                            // En mode retour
                            if (reverse) {
                                robot.adjustIntersection();
                                changeState(TURN_RETOUR);
                            }
                            // En mode aller
                            else {
                                changeState(ADJUST_INTER_DETECT);
                            }
                        }
                        // S'il y a un obstacle sur Ax
                        else {
                            // Dépasser l'intersection
                            robot.followLine(5);
                        }
                    }

                    break;

                case DETECT:
                    // S'il y a un obstacle sur Ax
                    if (thereIsObstacle(position)) {  
                        obstacles |= 1 << position;
                    }
                    changeState(TURN_SEND); // Tourner

                    break;

                case DETECT_NEW_LINE:
                    // S'il y a un obstacle sur A(x+1)
                    if (thereIsObstacle(position + 1)) {
                        obstacles |= 1 << (position + 1);
                    }
                    changeState(SEND_DATA_NEW_LINE);    // Tourner

                    break;
              
                case ADJUST_INTER_NEW_LINE:
                    robot.adjustIntersection();
                    changeState(TURN_NEW_LINE);

                    break;
              
                case ADJUST_INTER_DETECT:
                    robot.adjustIntersection();
                    changeState(TURN_DETECT);

                    break;

                case TURN_SEND:
                    turnSendB();
                    changeState(SEND_DATA);

                    break;

                case TURN_NEW_LINE:
                    turnNewLineB();
                    changeState(DETECT_NEW_LINE);

                    break;

                case TURN_DETECT:
                    turnDetectB();
                    changeState(DETECT);

                    break;

                case TURN_RETOUR:
                    turnRetourB();
                    changeState(RETOUR);

                    break;

                case RETOUR:
                    // Following
                    robot.followLine();

                    // À une intersection
                    if (robot.intersectionDetected()) {
                        if (position == 7) {
                            robot_->turnLeft90();
                            line = LIGNE_A;
                            changeState(SAVE);
                        }
                        else {
                            changeState(ADJUST_INTER_NEW_LINE);
                        }
                    }

                    break;

                case SEND_DATA_NEW_LINE:
                    // Si aucun obtacle n'est présent:
                    if (!(obstacles >> (position + 1))) {
                        robot.emettre(0);
                        line = LIGNE_A;
                        changeState(AVANCER);
                    }
                    // Si oui
                    else {
                        robot.emettre(1);
                        line = LIGNE_A;
                        changeState(TURN_DETOUR);
                    }

                    break;

                case SEND_DATA:
                    // Si aucun obtacle n'est présent:
                    if (!(obstacles >> position)) {
                        robot.emettre(0);
                        changeState(TURN_RETOUR);
                    }
                    // Si oui
                    else {
                        robot.emettre(1);
                        changeState(AVANCER);
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
