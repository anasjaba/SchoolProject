#define ADDRESS 0x05

#ifndef F_CPU
# warning "F_CPU pas defini pour 'Emetteur.cpp'"
# define F_CPU 8000000UL
#endif
#include "Emetteur.h"
#include "../../libpout/src/pwmIrc.h"
#include <avr/io.h>
#include <avr/delay.h>
using namespace libpout;


Emetteur::Emetteur() : pwm(105) {} // TOP = 8MHz / 38kHz / 2 ~= 105

void Emetteur::start(){
	pwm.start();
}

void Emetteur::stop(){
	pwm.stop();
}

void Emetteur::sendSequence(const uint8_t message){
	uint8_t nbT = 0;
	signalStart(nbT);

	for(uint8_t i = 0; i < 7; i++){						// Message, bits 0 à 6 (7-bits)
		pulse((message & (1 << i)) && (1 << i), nbT);	// sélection du i-ième bit à partir du LSB
		wait(nbT);
	}
	for(uint8_t i = 0; i < 5; i++){						// Adresse, bits 0 à 4 (5-bits)
		pulse((ADDRESS & (1 << i)) && (1 << i), nbT);	// sélection du i-ième bit à partir du LSB
		wait(nbT);
	}

	for(nbT; nbT < 75; nbT++){							// Après signal, off pendant 45000us - temps du signal
		_delay_loop_2(1200);
	}
}

void Emetteur::sendSequenceN(const uint8_t message, const uint8_t n){
	for(uint8_t i = 0; i < n; i++){
		sendSequence(message);
	}
}

void Emetteur::pulse(uint8_t bit, uint8_t& nbT){
	start();
	if(bit){
		_delay_loop_2(2400);	// 600 us
		nbT += 2;
	} else {
		_delay_loop_2(1200);	// 600 us
		nbT += 1;
	}
}

void Emetteur::wait(uint8_t& nbT){
	stop();
	_delay_loop_2(1200);		// 600 us
	nbT += 1;
}

void Emetteur::signalStart(uint8_t& nbT){
	start();
	_delay_loop_2(4800);		// 2400 us
	nbT += 4;
	wait(nbT);
}