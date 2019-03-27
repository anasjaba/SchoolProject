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
#define F_CPU 8000000UL

#include "pwm.h"

using namespace libpout;


PWM::PWM(OCR port)
{
	port_ = port;
	init();
}

PWM::PWM(OCR port, uint8_t ratio255)
{
	port_ = port;
	init();
	adjust(ratio255);
}

void PWM::init()
{
    // Counter to 0
    TCNT1 = 0;

    TCCR1A |= _BV(WGM10); // PWM, Phase Correct, 8-bit

	// division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = _BV(CS11);
}

void PWM::adjust(uint8_t ratio255)
{
	switch(port_) {
		case A0:
			OCR0A = ratio255;
			break;
		case A1:
			OCR1A = ratio255;
			break;
		case B1:
			OCR1B = ratio255;
			break;
		default:
			break;
	}
}

void PWM::start()
{
	switch(port_) {
		case A1:
			TCCR1A |= _BV(COM1A1) | _BV(COM1A0); // Set OC1A on Compare Match (Set output to high level).
			break;
		case B1:
			TCCR1A |= _BV(COM1B1) | _BV(COM1B0); // Set OC1B on Compare Match (Set output to high level).
			break;
		default:
			break;
	}
}

void PWM::stop()
{
	switch(port_) {
		case A1:
			TCCR1A &= ~(_BV(COM1A1)) & ~(_BV(COM1A0)); 
			break;
		case B1:
			TCCR1A &= ~(_BV(COM1B1)) & ~(_BV(COM1B0));
			break;
		default:
			break;
	}
}
