#include "Cytron.h"
#include <avr/io.h>

Cytron::Cytron(){}

void Cytron::refresh(){
	for(uint8_t i; i < 5; i++){
		senseurs[i] = PORTA | i;
	}
}

bool Cytron::getSenseur(uint8_t i) {
	return senseurs[i];
}