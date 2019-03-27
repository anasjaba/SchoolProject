/**
 * Copyright © 2014
 * Louis Racicot <info@louisracicot.com>, Samuel Rondeau, Weiwei Liang, Feriel Charfeddine
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */
#ifndef F_CPU
# warning "F_CPU pas defini pour 'led.cpp'"
# define F_CPU 8000000UL
#endif

#include "libpout/src/led.h"
#include "ledManager.h"

using namespace libpout;

/*
 * Construire toutes les led selons nos branchements
 * */
ledManager::ledManager()
{
    tableauLed_[0] = led(Ports::A, 0, 1);
}
/*
 * Destructeur
 * */
ledManager::~ledManager()
{
  /*for (uint8_t i = 0 ; i < nbLed ; i++)
    delete tableauLed_[i];*/
}
/*
 * allumer en rouge les DEL dont les bits correspondants de l'opérande sont à un.
 * */
void ledManager::lightOn(uint8_t numDel)
{
	for (int i = 0 ; i < nbLed ; i++)
	{
	  if (numDel >> i && 1)
	    tableauLed_[i].lightOnRed();
	}
}

/*
 * éteindre les DEL dont les bits correspondants de l'opérande sont à un.
 * */
void ledManager::lightOff(uint8_t numDel)
{
	for (int i = 0 ; i < nbLed ; i++)
	{
	  if (numDel >> i && 1)
	  {
	    tableauLed_[i].lightOff();
	  }
	  
	}
}
