/**************************************************************************
*Classe: distanceSensor
*Description: L'implémentation de classe MoteurManager.
*Éditeure: Weiwei LIANG, Feriel charfeddine, Louis Racicot & Samuel Rondeau
*La date: 2014-11-19
**************************************************************************/
//#include "../../libpout/src/sleep.h"
//#include "../../libpout/src/pwm.h"
#include "distanceSensor.h"
#include "can.h"
using namespace std;



/**********************************************************************************
*Fonction: bool detecter();
*Description: L'implémentation de la fonction qui permet de detecter les intersections
*Paramètre: uint8_t limite (la valeur minimale que retourne le can a une certaine distance)
*Valeur de retour: booleen
*********************************************************************************/
bool distanceSensor::detecter(uint8_t limite)
{
	nbDetection = 0;			//nombre de détection effectuées par le capteur
	can conv = can();			//construire un can pour traduire le signale reçu par le capteur
	for (uint8_t i = 0; i < 100 ; i++)
	{
	  if ((conv.lecture(0) >> 2) > limite)	//si la valeur retournée par le can est supérieure à 10
	    nbDetection ++;			//incrémenter le nombre d'intersection
	}
	if (nbDetection > 85)			//si 85% des valeurs retournées 
	  return true;
	else return false;
}
