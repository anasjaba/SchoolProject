/************************************************************************************
*	Fichier					: Piezoelectrique.h                                     *
*	Auteurs					: Samuel Rondeau                                        *
*                           : Louis Racicot                                         *
*                           : Feriel Charfeddine                                    *
*                           : Weiwei Liang                                          *
*	Description				: Declaration de la classe Piezoelectrique              *
*                           : Permet de générer des sons                            *
*	Date de creation		: 5 novembre 2014                                       *
*	Date de modification	: 7 novembre 2014                                       *
************************************************************************************/

#ifndef PIEZOELECTRIQUE_H
#define PIEZOELECTRIQUE_H

#include "../../libpout/src/pwmSon.h"
using namespace libpout;

class Piezoelectrique
{
public:
	Piezoelectrique();
	Piezoelectrique(uint8_t frequency);
	~Piezoelectrique();

	void start();
	void stop();

	void setFrequency(uint8_t note);

private:
	pwmSon generateur_;
	uint8_t demPeriode[37];
};

#endif /* PIEZOELECTRIQUE_H */