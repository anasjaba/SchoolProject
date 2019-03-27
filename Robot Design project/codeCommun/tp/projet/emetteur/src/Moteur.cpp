/**************************************************************************
*Classe: Moteur
*Description: L'implémentation de classe Moteur.
*Éditeure: Weiwei LIANG , Feriel charfeddine, Louis Racicot & Samuel Rondeau
*La date: 2014-11-05
**************************************************************************/
#include "Moteur.h"

using namespace std;
using namespace libpout;

Moteur::Moteur(Position position): direction_(1), position_(position)
{
	if (position_ == Right) {
		pwm_ = PWM(OCR::A1);
	} else {
		pwm_ = PWM(OCR::B1);
	}
}

/**********************************************************************************
*Fonction: void demarrer(uint8_t ratio255);
*Description: L'implémentation de la fonction qui permet de demarrer le robot
*Paramètre: le ratio255 
*Valeur de retour: aucun.
*********************************************************************************/
void Moteur::demarrer(uint8_t ratio255)
{
	pwm_.start();
	pwm_.adjust(ratio255);
}

/**********************************************************************************
*Fonction: void arreter();
*Description: L'implémentation de la fonction qui permet d'arrêter le robot
*Paramètre: aucun
*Valeur de retour: aucun.
*********************************************************************************/
void Moteur::arreter()
{
	pwm_.stop();
}

/**
 * L'implémentation de la fonction qui permet de changer la direction du robot
 *
 * Paramètre:
 * 	- direction (0 = Reculer, 1 = Avancer)
 */
void Moteur::setDirection(bool direction)
{
	if (direction) {
		// Reculer
		if (position_ == Left) {
			PORTD &= ~(0x04);
		} else {
			PORTD &= ~(0x08);
		}

	} else {
		// Avancer
		if (position_ == Left) {
			PORTD |= 0x04;
		} else {
			PORTD |= 0x08;
		}
	}
}
