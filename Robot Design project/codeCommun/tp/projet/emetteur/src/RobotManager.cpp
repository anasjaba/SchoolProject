/**
 * @author Louis Racicot & Samuel Rondeau & Feriel Charfeddine & Liang Weiwei
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include "RobotManager.h"
using namespace libpout;

/*
*  Détecte la présence ou l'absence d'un obstacle à une intersection
*/
bool RobotManager::detecter(uint8_t limite)
{
    uint8_t nbDetection = 0;                //nombre de détection effectuées par le capteur
                
    for (uint8_t i = 0; i < 10 ; i++)
    {
        //_delay_ms(500);
      if ((conv.lecture(0) >> 2) > limite)  //si la valeur retournée par le can est supérieure à 10
        nbDetection ++;                     //incrémenter le nombre d'intersection
        _delay_ms(2);
    }

    if (nbDetection > 8){                  //si 85% des valeurs retournées 
        jouerSon();
        return true;
  }
    else return false;
}

/*
*  Suit une ligne en procédant à des ajustements pour rester en ligne droite
*/
void RobotManager::followLine()
{
    engines.avancer(vitesse);

    // 00010000 | 00110000 |00011000
    if (((PINC & 0x7C) == 0x10) || ((PINC & 0x7C) == 0x18) || ((PINC & 0x7C) == 0x30))  {
        // PORTA = 0x0;
        engines.adjustcenter();
        _delay_ms(10);
    }

    // 00001000 | 00000100 | 00001100
    if (((PINC & 0x7C) == 0x04) || ((PINC & 0x7C) == 0x0C) || ((PINC & 0x7C) == 0x08)) {
        //PORTA = 0x2;
        engines.adjustToLeft();
        _delay_ms(10);
    }

    // 01100000 | 01000000 | 00100000
    if (((PINC & 0x7C) == 0x60) || ((PINC & 0x7C) == 0x40) || ((PINC & 0x7C) == 0x20)) {
    // PORTA = 0x1;
        engines.adjustToRight();
        _delay_ms(10);
    }
}

/*
*  Utilise followLine() pendant un certain nombre de 100ms
*/
void RobotManager::followLine(uint8_t ms100)
{
    while (ms100 > 0) {
        followLine();
        _delay_ms(100);
        ms100--;
    }
}

/*
*  Détecte une intersection
*/
bool RobotManager::intersectionDetected()
{
    // Détection d'intersection: 01111100 | 00011100 | 01110000 | 00111100 | 01111000
    if (((PINC & 0x7C) == 0x7C) || ((PINC & 0x7C) == 0x1C) || ((PINC & 0x7C) == 0x70) ||((PINC & 0x7C) == 0x3C)||((PINC & 0x7C) == 0x78)) {
        _delay_ms(15);

        if(((PINC & 0x7C) == 0x7C) || ((PINC & 0x7C) == 0x1C) || ((PINC & 0x7C) == 0x70) ||((PINC & 0x7C) == 0x3C)||((PINC & 0x7C) == 0x78)) {
            return true;
        }
    }

    return false;
}

/*
*  Utilise detecter() pour s'assurer de la position des obstacles et balayant le champ de vision
*/
bool RobotManager::detectPoteau()
{
    bool detected = 0;

    engines.arreter();
    _delay_ms(250);
    
    detected |= detecter(80);
    _delay_ms(100);

    //incliner légèrement à gauche, arrêter puis tester les potaux
    if(!detected){
        while((PINC & 0x7C) != 0x00 && !detected){
            engines.tournerGauche(0);
            detected |= detecter(80);
            _delay_ms(10);
        }
        engines.arreter();
        _delay_ms(250);

        // Revenir
        while((PINC & 0x10) != 0x10){
            engines.tournerDroite(0);
            detected |= detecter(80);
            _delay_ms(10);
        }
        engines.arreter();
        _delay_ms(250);
    }
    
    if(!detected){
        //incliner légèrement à droite, arrêter puis tester les potaux
        while((PINC & 0x7C) != 0x00 && !detected){
            engines.tournerDroite(0);
            detected |= detecter(80);
            _delay_ms(10);
        }
        engines.arreter();
        _delay_ms(250);
    
        // Revenir
        while((PINC & 0x10) != 0x10){
            engines.tournerGauche(0);
            detected |= detecter(80);
            _delay_ms(10);
        }
        engines.arreter();
    }

    if (!detected) {
        detected |= detecter(80);
        _delay_ms(100);
    }

    return detected;
}

/*
*  Avance légèrement le robot à une intersection pour le redresser pour tourner
*/
void RobotManager::adjustIntersection()
{
    engines.avancer(250);
    _delay_ms(50);
    engines.avancer(vitesse+40);
    _delay_ms(100);
    followLine(8);  // entre 8 et 11 selon les batteries
}

/*
*  Tourne de 90 degrés vers la droite
*/
void RobotManager::turnRight90()
{
    engines.arreter();
    _delay_ms(250);
    engines.tournerDroite(45);
    
     engines.adjustToRight();
    _delay_ms(300);

    while ((PINC & 0x7C) == 0x00) {
        engines.tournerDroite(0);
    }

    engines.arreter();
}

/*
*  Tourne de 90 degrés vers la gauche
*/
void RobotManager::turnLeft90()
{
    engines.arreter();
    _delay_ms(250);
    engines.tournerGauche(45);

    while ((PINC & 0x7C) == 0x00) {
        engines.tournerGauche(0);
    }

    engines.arreter();
}

/*
*  Fait un demi-tour
*/
void RobotManager::turn180()
{
    turnRight90();
    turnRight90();
}

/*
*  Transmet par infrarouge les informations du parcours au récepteur
*/
void RobotManager::emettre(uint8_t message)
{
    emetteur.sendSequence(message, 15);
    msleep(50);
    emetteur.sendSequence(message, 15);
    msleep(50);
    emetteur.sendSequence(message, 15);
    msleep(50);
}

/*
*  Joue un son à une fréquence fixe pré-établie
*/
void RobotManager::jouerSon(){
    piezo.setFrequency(75);
    piezo.start();
    _delay_ms(100);
    piezo.stop();
}
