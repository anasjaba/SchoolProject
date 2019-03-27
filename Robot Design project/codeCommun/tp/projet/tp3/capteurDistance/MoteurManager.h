/**************************************************************************
*Classe: Moteur
*Description: Une classe qui contient les fonctions de s'arrêter, d'avancer,
*             de reculer, de tourner à gauche et de tourner à droite.
*Éditeure: Weiwei LIANG, Feriel charfeddine, Louis Racicot & Samuel Rondeau
*La date: 2014-11-05
**************************************************************************/
#pragma once

#include "Moteur.h"

class MoteurManager
{
public:
   	MoteurManager(): moteurD(Position::Right) , moteurG(Position::Left) {}
	~MoteurManager(){}
	
	/*Les méthodes pour faire bouger du robot à la façon différente*/
	void avancer(uint8_t ratio255); 				
	void reculer(uint8_t ratio255);
	void arreter(); 
	void tournerDroite(uint8_t);
	void tournerGauche(uint8_t);
	void adjustToRight();
	void adjustToLeft();
	void adjustcenter();
	
private:
	Moteur moteurD;
	Moteur moteurG;
};
