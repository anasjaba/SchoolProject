/************************************************************************************
*	Fichier					: Piezoelectrique.cpp                                   *
*	Auteurs					: Samuel Rondeau                                        *
*                           : Louis Racicot                                         *
*                           : Feriel Charfeddine                                    *
*                           : Weiwei Liang                                          *
*	Description				: Implementation de la classe Piezoelectrique           *
*                           : Permet de générer des sons                            *
*	Date de creation		: 5 novembre 2014                                       *
*	Date de modification	: 5 novembre 2014                                       *
************************************************************************************/

#define F_CPU 8000000UL

#include "Piezoelectrique.h"
using namespace std;

Piezoelectrique::Piezoelectrique()
{

}

Piezoelectrique::~Piezoelectrique()
{

}

Piezoelectrique::start()
{

}

Piezoelectrique::stop()
{

}

Piezoelectrique::setFrequency(int note)
{
	// f(n) = 8.175798918*exp(0.057762265*x)
	frequency_ = 
}