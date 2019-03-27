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
# warning "F_CPU pas defini pour 'pwmSon.cpp'"
# define F_CPU 8000000UL
#endif

#include "pwmSon.h"

using namespace std;


PwmSon::PwmSon()
{
	init();
}

PwmSon::PwmSon(uint8_t ratio255)
{
	init();
	adjust(ratio255);
}

void PwmSon::init()
{
    // Counter to 0
    TCNT0 = 0;

    TCCR0A |= _BV(COM0A0); // PWM, Phase Correct, 8-bit ; Toggle OC0A on Compare Match.

	// division d'horloge par 256
    TCCR0B = _BV(CS02);
}

void PwmSon::adjust(uint8_t ratio255)
{
	OCR0A = ratio255;
}

void PwmSon::start()
{
	TCCR0A |= _BV(COM0A1) | _BV(COM0A0); // Set OC0A on Compare Match (Set output to high level).
}

void PwmSon::stop()
{
	TCCR0A &= ~(_BV(COM0A1)) & ~(_BV(COM0A0)); 
}