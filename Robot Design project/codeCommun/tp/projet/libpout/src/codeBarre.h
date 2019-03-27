/**
 *
 * @author Louis Racicot & Samuel Rondeau & Feriel Charfeddine & Weiwei
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */

#pragma once
#define F_CPU 8000000UL
#define debug true
#include <avr/io.h>
#include <util/delay.h>
#include "../../libpout/src/serial.h"

bool readBlanc();
bool readNoir();
uint8_t lireCodeBarre();

