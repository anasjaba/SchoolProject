#define F_CPU 8000000UL
#include <avr/io.h>
#include "../../libpout/src/serial.h"
#include "../../libpout/src/pwmIrc.h"
#include "Emetteur.h"
#define debug true
using namespace libpout;

Serial usb;

void init()
{
	// PWM output for IR emitter
	DDRD = 0xC0; 		// OC2A on D7
	PORTD &= 0xBF;		// 0 on D6

	if (debug) {
		usb = Serial();
	}
}

int main(){
	init();
	Emetteur emetteur;
	uint8_t op = 0x43;
	//for(uint8_t op = 0x00; op < 0x7F; op++){
	//for(uint8_t op = 0x00; op < 0x10; op++){
	for(;;){
		emetteur.sendSequence(op);
	}

	return 0;
}