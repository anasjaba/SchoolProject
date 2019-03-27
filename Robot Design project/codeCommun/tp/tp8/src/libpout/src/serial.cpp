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
# warning "F_CPU pas defini pour 'serial.cpp'"
# define F_CPU 8000000UL
#endif

#include "serial.h"

using namespace libpout;

Serial::Serial()
{
	init();
}

void Serial::init()
{
	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0
	UCSR0A = _BV(UDRE0);
	UCSR0B = _BV(RXEN0)| _BV(TXEN0);

	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

void Serial::send(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while (!( UCSR0A & (1<<UDRE0)));

	/* Put data into buffer, sends the data */
	UDR0 = data;
}