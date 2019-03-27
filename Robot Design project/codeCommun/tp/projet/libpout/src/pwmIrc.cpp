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
# warning "F_CPU pas defini pour 'pwmIrc.cpp'"
# define F_CPU 8000000UL
#endif

#include "pwmIrc.h"

using namespace libpout;


pwmIrc::pwmIrc()
{
	init();
}

pwmIrc::pwmIrc(uint8_t max)
{
	init();
	adjust(max);
}

void pwmIrc::init()
{
    // Counter to 0
    TCNT2 = 0;

    TCCR2A |= _BV(WGM21); // CTC

	// aucun diviseur d'horloge
    TCCR2B |= _BV(CS20);
}

void pwmIrc::adjust(uint8_t max)
{
	OCR2A = max;
}

void pwmIrc::start()
{
	TCCR2A |= _BV(COM2A0) | _BV(WGM21); // Toggle OC0A on Compare Match (Set output to high level), mode CTC.
}

void pwmIrc::stop()
{
	TCCR2A &= ~(_BV(COM2A0)) & ~(_BV(WGM21)); 
}