/************************************************************************************
*	Fichier					: Piezoelectrique.cpp                                   *
*	Auteurs					: Samuel Rondeau                                        *
*                           : Louis Racicot                                         *
*                           : Feriel Charfeddine                                    *
*                           : Weiwei Liang                                          *
*	Description				: Implementation de la classe Piezoelectrique           *
*                           : Permet de générer des sons                            *
*	Date de creation		: 5 novembre 2014                                       *
*	Date de modification	: 7 novembre 2014                                       *
************************************************************************************/

#define F_CPU 8000000UL
#include "Piezoelectrique.h"
#include "../../libpout/src/pwmSon.h"
#include <avr/io.h>

using namespace libpout;

Piezoelectrique::Piezoelectrique() : generateur_(0)
{
	// Temps actif (pwm) = (ms) * 8MHz / 256(prescaler)
	uint8_t periode[] = {142, 134, 127, 119, 113,		// 45 - 49
			106, 100, 95, 89, 84, 80, 75, 71, 67, 63,	// 50 - 59
			60, 56, 53, 50, 47, 45, 42, 40, 38, 36,		// 60 - 69
			34, 32, 30, 28, 27, 25, 24, 22, 21, 20,		// 70 - 79
			19, 18};									// 80 - 81

	for (uint8_t i = 0; i < 37; i++) {
		demPeriode[i] = periode[i];
	}
}

Piezoelectrique::Piezoelectrique(uint8_t frequency) : generateur_(frequency)
{
	// Temps actif (pwm) = (ms) * 8MHz / 256(prescaler)
	uint8_t periode[] = {142, 134, 127, 119, 113,		// 45 - 49
			106, 100, 95, 89, 84, 80, 75, 71, 67, 63,	// 50 - 59
			60, 56, 53, 50, 47, 45, 42, 40, 38, 36,		// 60 - 69
			34, 32, 30, 28, 27, 25, 24, 22, 21, 20,		// 70 - 79
			19, 18};									// 80 - 81

	for (uint8_t i = 0; i < 37; i++) {
		demPeriode[i] = periode[i];
	}

}

Piezoelectrique::~Piezoelectrique(){}

void Piezoelectrique::start()
{
	generateur_.start();
}

void Piezoelectrique::stop()
{
	generateur_.stop();
}

void Piezoelectrique::setFrequency(uint8_t note)
{
	if(note >= 45 && note <= 81){
		generateur_.adjust(demPeriode[note - 45]);
	}
}