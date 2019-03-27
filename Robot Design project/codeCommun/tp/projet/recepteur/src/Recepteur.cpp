#define F_CPU 8000000UL
#include "Recepteur.h"
#include <avr/io.h>
#include "../../libpout/src/serial.h"

Recepteur::Recepteur() 
	: IR_idle(true),
	  IR_started(false),
	  IR_waiting_data(false),
	  IR_data_counter(false),
	  IR_data_ready(false),
	  IR_wait_timeout(false),
	  IR_data(false) {}

uint8_t Recepteur::isDataReady()
{
	return IR_data_ready;
}

uint8_t Recepteur::getData()
{
	if (IR_data_ready) {
		IR_data_ready = 0;

		return (IR_data & 0x7F) >> 1;
	}

	return 0;
}

void Recepteur::partirMinuterie(uint16_t duree_us)
{
    // mode CTC du timer 1, 64 bits pre scaling
    // interruption après la duree specifiee
    TCNT2 = 0;
    if (duree_us == 2500) {
		//PORTA |= 0x04;
    	OCR2A = 161;
    }
    if (duree_us == 1200) {
    	OCR2A = 77;
    }
    if (duree_us == 900) {
		//PORTA |= 0x04;
    	OCR2A = 57;
    }
    TCCR2A |= _BV(COM2A0) | _BV(WGM21);
    TCCR2B |= _BV(CS22) | _BV(CS20); // 00001101; WGM12 = CTC mode, 
    TIMSK2 |= _BV(OCIE2A); //00000010;
}

void Recepteur::arreterMinuterie()
{
    TCNT2 = 0;
    TCCR2A = 0;
    TCCR2B = 0;
    TIMSK2 = 0;
}

void Recepteur::IR_abort()
{
	IR_idle = 1;
	IR_started = 0;
	IR_waiting_data = 0;
	IR_data_counter = 0;
	IR_data_ready = 0;
	IR_data = 0;
	IR_wait_timeout = 0;
}

void Recepteur::dataReady()
{
	IR_idle = 1;
	IR_started = 0;
	IR_waiting_data = 0;
	IR_data_counter = 0;
	IR_data_ready = 1;
}

void Recepteur::ISR_INT_vect()
{
	IR_wait_timeout = 0;

	// Idle
	if (IR_idle) {
		IR_idle = false;
		IR_data = 0;
    	partirMinuterie(2500);
	}

	// Data receive mode
	else if (IR_started && !IR_waiting_data) {
		IR_waiting_data = true;
    	partirMinuterie(900);
	}

	// Start signal has been detected, but sequence has not started
	// Or we are already waiting for the data counter
	else {
		IR_abort();
	}
}

void Recepteur::ISR_TIMER_COMP_vect()
{
	if (IR_wait_timeout == 1) {
		arreterMinuterie();
		IR_abort();
		return;
	}

	//PORTA &= ~(0x04);
	IR_wait_timeout = 1;
    partirMinuterie(1200);
    //IR_data = 0;
	// Get data
	if (IR_started) {
		// Sample the data (LSB first)
		if ( ((PINB & 0x04) && (PINB & 0x04)) == 0) {
			IR_data |= 1 << IR_data_counter;
		}

		IR_waiting_data = false;
		//PORTA &= ~(0x08);

	} else { // Check start Signal
		if (((PINB & 0x04) && (PINB & 0x04)) == 1) {
			IR_started = true;
		} else {
			IR_abort();
		}
	}

	if (++IR_data_counter > 12) {
		if (IR_data >> 8 == 0x5) {
			dataReady();
		} else {
			IR_abort();
		}
	}
}
