/**************************************************************************
*Classe: Moteur
*Description: Une classe qui gère la détection d'obstacle
*Éditeure: Weiwei LIANG, Feriel charfeddine, Louis Racicot & Samuel Rondeau
*La date: 2014-11-19
**************************************************************************/
#include <avr/io.h>

#pragma once


class distanceSensor
{
public:
   	distanceSensor(): nbDetection(0) {}
	~distanceSensor(){}
	
	// la méthode pouc confirmer la détection des potaux
	bool detecter(uint8_t limite); 				
	
	
private:
	uint8_t nbDetection;
};


//arrêter le moteur à l'intersection
				/*engines.arreter();
				_delay_ms(500);
				
				//incliner légèrement à droite, arrêter puis tester les potaux
				engines.adjustToRight();
				_delay_ms(200);
				engines.arreter();
				_delay_ms(500);
				detectedRight = detecter(30);
				
				//incliner légèrement à gauche, arrêter puis tester les potaux
				engines.adjustToLeft();
				_delay_ms(200);
				engines.arreter();
				_delay_ms(500);
				detectedLeft = detecter(10);
				
				//usb.send(detected);
				if (detectedRight || detectedRight)		//si un des deux tests est correct
				 state = TURN_RIGHT;				//tourner
				else
				  state = AVANCER;				//sinon continuer
				break;*/