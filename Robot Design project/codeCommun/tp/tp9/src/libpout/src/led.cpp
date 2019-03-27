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

#include "led.h"

using namespace libpout;


led::led(Ports port, uint8_t pin1, uint8_t pin2)
{
	if (pin1 == pin2 || pin1 > 7 || pin2 > 7) {
		return;
	}

	port_ = port;

	// DMUX. For example, if pin1 = 3, than pin1_= 00001000.
	pin1_ = 0x1 << pin1;
	pin2_ = 0x1 << pin2;
}

void led::lightOnRed()
{
	switch (port_) {
		// We only want the "pin1" to be set to "1"
		// So if "pin1" is for example the fourth pin (pin1=00001000)
		// PORTA |= 00001000;
		// This means:
		//    xxxxxxxx
		// |= 00001000
		//    --------
		//    xxxx1xxx
		//
		// We also want the other pin to be set to "0"
		// So if "pin2" is for example the third pin (pin2=00000100)
		// PORTA &= ~(0000100);
		// This means:
		//    xxxx1xxx
		// &= 11111011
		//    --------
		//    xxxx10xx
        //
		// That way the electricity goes in the right direction!
		case A:
			PORTA |= pin1_;
			PORTA &= ~pin2_;
		case B:
			PORTB |= pin1_;
			PORTB &= ~pin2_;
		case C:
			PORTC |= pin1_;
			PORTC &= ~pin2_;
		case D:
			PORTD |= pin1_;
			PORTD &= ~pin2_;
	}
}

void led::lightOnGreen()
{
	switch (port_) {
		case A:
			PORTA |= pin2_;
			PORTA &= ~pin1_;
		case B:
			PORTB |= pin2_;
			PORTB &= ~pin1_;
		case C:
			PORTC |= pin2_;
			PORTC &= ~pin1_;
		case D:
			PORTD |= pin2_;
			PORTD &= ~pin1_;
	}
}

void led::lightOff()
{
	switch (port_) {
		case A:
			PORTA &= ~pin1_;
			PORTA &= ~pin2_;
		case B:
			PORTB &= ~pin1_;
			PORTB &= ~pin2_;
		case C:
			PORTC &= ~pin1_;
			PORTC &= ~pin2_;
		case D:
			PORTD &= ~pin1_;
			PORTD &= ~pin2_;
	}
}
