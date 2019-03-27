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
#pragma once

#include <avr/io.h>
#include "libpout/src/led.h"	
#define nbLed 1
using namespace libpout;

/**
  * The class represent LED. It can be on or off.
  */
class ledManager
{
	public:
		
		ledManager();
		~ledManager();

		/**
		  * Light on the LED et Nous devons spécifier quelle 
		  * del nous souhaitons allumer .
		  */
		void lightOn(uint8_t numDel);

		/**
		  * Light off the LEDNous devons spécifier quelle 
		  * del nous souhaitons éteindre .
		  */
		void lightOff(uint8_t numDel);

	private:
		led tableauLed_[nbLed];	//Un tableau de led pour gérer toutes les led

};