#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../../libpout/src/serial.h"
#include "Recepteur.h"

#define debug true

using namespace libpout;

Serial usb;
Recepteur recepteur;

volatile uint16_t received_data = 0;

ISR (INT2_vect)
{
	// Rising
	if (PINB == 0x04) {
		PORTA |= 0x02; // debug
	
	// Falling edge
	} else if (PINB == 0x00) {
		_delay_loop_1(1);
		PORTA &= ~(0x02); // debug
		recepteur.ISR_INT_vect();
	}

    // Voir la note plus bas pour comprendre cette instruction et son role
    EIFR |= (1 << INTF0);
}

ISR (TIMER2_COMPA_vect)
{
	recepteur.ISR_TIMER_COMP_vect();

	if (recepteur.isDataReady()) {
		received_data = recepteur.getData();
		usb.send(received_data);
	}
}

void init()
{
    cli ();

	// Interrupt INT2 for IR receiver
	DDRD &= 0x00; // INT2 = 0;

	DDRB = 0x03; // LED

	//DEBUG
	DDRA = 0xFF;// debug
	PORTA |= 0x02;// debug

	// Permettre les interruptions externes
    EIMSK |= _BV(INT2);

    // Sensibiliser les interruptions externes
    EICRA |= _BV(ISC20); // Any edge

    sei();

    //recepteur = Recepteur();

	if (debug) {
		usb = Serial();
	}
}

int main()
{
	init();

	for(;;){}

	return 0;
}