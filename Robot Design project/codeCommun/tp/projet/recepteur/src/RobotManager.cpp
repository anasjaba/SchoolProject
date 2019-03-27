/**
 * @author Louis Racicot & Samuel Rondeau & Feriel Charfeddine & Liang Weiwei
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include "RobotManager.h"
using namespace libpout;

/*
*  Suit une ligne en procédant à des ajustements pour rester en ligne droite
*/
void RobotManager::followLine()
{
    engines.avancer(vitesse);
    // 10001000
    if ((PINA & 0xA8) == 0x88)  {
            engines.adjustcenter();
            _delay_ms(1);
        }
       // 00101000
        if ((PINA & 0xA8) == 0x28) {
             engines.adjustToRight();
            _delay_ms(1);
        }
	/// 10100000
        if ((PINA & 0xA8) == 0xA0) {
	   engines.adjustToLeft();
            _delay_ms(1);
        }
}

/*
*  Détecte une intersection
*/
bool RobotManager::intersectionDetected()
{	//00000000 | 10000000 | 00001000
    if (((PINA & 0xA8) == 0x00) || ((PINA & 0xA8) == 0x80) || ((PINA & 0xA8) == 0x08) ) {

        _delay_ms(5);
	//00000000 | 10000000 | 00001000
        if (((PINA & 0xA8) == 0x00) || ((PINA & 0xA8) == 0x80) || ((PINA & 0xA8) == 0x08) ) {
            return true; 
        }
    }

    return false;
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
*  Avance légèrement le robot à une intersection pour le redresser pour tourner
*/
void RobotManager::adjustIntersection()
{
    engines.avancer(vitesse+40);
    _delay_ms(100);

    followLine(11);
}

/*
*  Tourne de 90 degrés vers la droite
*/
void RobotManager::turnRight90()
{
    engines.arreter();
    _delay_ms(250);
    engines.tournerDroite(45);

    while ((PINA & 0xA8) == 0xA8) {
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

    while ((PINA & 0xA8) == 0xA8) {
        engines.tournerGauche(0);
    }

    engines.arreter();
}

/*
*  Fait un demi-tour
*/
void RobotManager::turn180()
{
    turnLeft90();
    turnLeft90();
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