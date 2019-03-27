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
# warning "F_CPU pas defini pour 'pwm.cpp'"
# define F_CPU 8000000UL
#endif

#include "pwm.h"

using namespace libpout;


PWM::PWM(OCR1 port)
{
	port_ = port;
	init();
}

PWM::PWM(OCR1 port, uint8_t ratio255)
{
	port_ = port;
	init();
	adjust(ratio255);
}

void PWM::init()
{
    TCCR1A |= _BV(WGM10); // PWM, Phase Correct, 8-bit

	// division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = _BV(CS11);
}

void PWM::adjust(uint8_t ratio255)
{
	switch(port_) {
		case A:
			OCR1A = ratio255;
			break;
		case B:
			OCR1B = ratio255;
			break;
	}
}

void PWM::start()
{
	switch(port_) {
		case A:
			TCCR1A |= _BV(COM1A1) | _BV(COM1A0); // Set OC1A on Compare Match (Set output to high level).
			break;
		case B:
			TCCR1A |= _BV(COM1B1) | _BV(COM1B0); // Set OC1B on Compare Match (Set output to high level).
			break;
	}
}

void PWM::stop()
{
	switch(port_) {
		case A:
			TCCR1A &= ~(_BV(COM1A1)) & ~(_BV(COM1A0)); //Set OC1A on disconnected mode
			break;
		case B:
			TCCR1A &= ~(_BV(COM1B1)) & ~(_BV(COM1B0)); //Set OC1B on disconnected mode 
			break;
	}
}