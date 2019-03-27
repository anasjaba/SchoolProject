/**
 * @author Louis Racicot & Samuel Rondeau & Feriel Charfeddine & Liang Weiwei
 * @modified: Look at the SVN
 */

#pragma once
#define F_CPU 8000000UL

#include "../../libpout/src/sleep.h"
#include "../../libpout/src/memoire_24.h"
#include "../../libpout/src/can.h"
#include "MoteurManager.h"
#include "RobotManager.h"
#include "Recepteur.h"
#include "Piezoelectrique.h"
using namespace libpout;

class RobotManager
{
public:
	RobotManager(): vitesse(140){}
	~RobotManager(){}

	/*
	*  Suit une ligne en procédant à des ajustements pour rester en ligne droite
	*/
	void followLine();

	/*
	*  Utilise followLine() pendant un certain nombre de 100ms
	*/
	void followLine(uint8_t ms100);

	/*
	*  Détecte une intersection
	*/
	bool intersectionDetected();

	/*
	*  Avance légèrement le robot à une intersection pour le redresser pour tourner
	*/
	void adjustIntersection();

	/*
	*  Tourne de 90 degrés vers la droite
	*/
	void turnRight90();

	/*
	*  Tourne de 90 degrés vers la gauche
	*/
	void turnLeft90();

	/*
	*  Fait un demi-tour
	*/
	void turn180();

	/*
	*  Joue un son à une fréquence fixe pré-établie
	*/
	void jouerSon();

private:
	uint8_t vitesse;		// vitesse de croisière
    MoteurManager engines;	// gestionnaire des moteurs
    can conv;				// convertisseur analogique-numérique
    Recepteur recepteur;	// récepteur infrarouge
    Piezoelectrique piezo;	// piézoélectrique
};
