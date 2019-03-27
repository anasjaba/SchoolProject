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
# warning "F_CPU pas defini pour 'sleep.cpp'"
# define F_CPU 8000000UL
#endif

#include "sleep.h"

void msleep(int ms) {
    for(int i = 0; i < ms; i++){
        _delay_loop_2(2000);
    }
}

void usleep(int us) {
    for(int i = 0; i < us; i++){
        _delay_loop_2(2);
    }
}