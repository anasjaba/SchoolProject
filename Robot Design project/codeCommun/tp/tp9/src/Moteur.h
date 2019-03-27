/**************************************************************************
*Classe: Moteur
*Description: Une classe qui contient les fonctions de s'arrêter, d'avancer,
*             de reculer, de tourner à gauche et de tourner à droite.
*Éditeure: Weiwei LIANG, Feriel charfeddine, Louis Racicot & Samuel Rondeau
*La date: 2014-11-05
**************************************************************************/
#pragma once
#include "libpout/src/pwm.h"

using namespace libpout;

enum Position { Left, Right };

class Moteur
{
   public:
	Moteur(Position position);
	~Moteur(){}
	
	void demarrer(uint8_t ratio255); 			//méthode pour arrêter le moteur.
	void arreter(); 					//méthode pour faire démarrer le moteur.
	void setDirection (bool direction);			//methode pour modofoer la direction
	
   private:
	PWM pwm_;
	bool direction_;
	Position position_;

};
