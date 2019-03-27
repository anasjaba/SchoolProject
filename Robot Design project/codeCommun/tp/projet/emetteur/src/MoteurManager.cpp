/**************************************************************************
*Classe: MoteurManager
*Description: L'implémentation de classe MoteurManager.
*Éditeure: Weiwei LIANG, Feriel charfeddine, Louis Racicot & Samuel Rondeau
*La date: 2014-11-05
**************************************************************************/
#define F_CPU 8000000UL
#include "../../libpout/src/sleep.h"
#include "../../libpout/src/pwm.h"
#include "Moteur.h"
#include "MoteurManager.h"

using namespace std;
using namespace libpout;

//CALIBRER LES ROUES DU ROBOTS
uint8_t modMD = 100;
uint8_t modMG = 90;
uint8_t speed;

/**********************************************************************************
*Fonction: void avancer(uint8_t ratio255);
*Description: L'implémentation de la fonction qui permet d'avancer le robot
*Paramètre: le ratio255 de type uint8_t
*Valeur de retour: aucun.
*********************************************************************************/
void MoteurManager::avancer(uint8_t ratio255)
{
	speed = ratio255;
	moteurD.setDirection(1);
	moteurG.setDirection(1);
	moteurD.demarrer(255-(speed*modMD/100));
	moteurG.demarrer(255-(speed*modMG/100));
}

/**********************************************************************************
*Fonction: void avancer(uint8_t ratio255);
*Description: L'implémentation de la fonction qui permet de reculer le robot
*Paramètre: le ratio255 de type uint8_t
*Valeur de retour: aucun.
*********************************************************************************/
void MoteurManager::reculer(uint8_t ratio255)
{
	speed = ratio255;
	moteurD.setDirection(0);
	moteurG.setDirection(0);
	moteurD.demarrer(255-(speed*modMD/100));
	moteurG.demarrer(255-(speed*modMG/100));
}

void MoteurManager::adjustToLeft()
{
	moteurD.demarrer(255-(speed*modMG/100));
	moteurG.arreter();
}

void MoteurManager::adjustToRight()
{
	moteurG.demarrer(255-(speed*modMG/100));
	moteurD.arreter();
}

void MoteurManager::adjustcenter()
{
	moteurD.demarrer(255-(speed*modMD/100));
	moteurG.demarrer(255-(speed*modMG/100));
}

/**********************************************************************************
*Fonction: void arreter();
*Description: L'implémentation de la fonction qui permet d'arrêter le robot
*Paramètre: aucun
*Valeur de retour: aucun.
*********************************************************************************/
void MoteurManager::arreter()
{
	moteurD.arreter();
	moteurG.arreter();
}


/**********************************************************************************
*Fonction: void tournerDroite();
*Description: L'implémentation de la fonction qui permet de tourner vers la droite
*Paramètre: aucun 
*Valeur de retour: aucun.
*********************************************************************************/
void MoteurManager::tournerDroite(uint8_t degree)
{
	moteurD.setDirection(0);
	moteurG.setDirection(1);
	moteurD.demarrer(140);
	moteurG.demarrer(140);

	if (degree > 0) {
		moteurD.demarrer(0);
		moteurG.demarrer(0);
		_delay_ms(50);
		moteurD.demarrer(140);
		moteurG.demarrer(140);

		msleep(14*degree);
		moteurD.arreter();
		moteurG.arreter();
	}
}

/**********************************************************************************
*Fonction: void tournerGauche();
*Description: L'implémentation de la fonction qui permet de tourner vers le gauche
*Paramètre: aucun
*Valeur de retour: aucun.
*********************************************************************************/
void MoteurManager::tournerGauche(uint8_t degree)
{
	moteurD.setDirection(1);
	moteurG.setDirection(0);
	moteurD.demarrer(140);
	moteurG.demarrer(140);

	if (degree > 0) {
		moteurD.demarrer(0);
		moteurG.demarrer(0);
		_delay_ms(50);
		moteurD.demarrer(140);
		moteurG.demarrer(140);

		msleep(14*degree);
		moteurD.arreter();
		moteurG.arreter();
	}
}
