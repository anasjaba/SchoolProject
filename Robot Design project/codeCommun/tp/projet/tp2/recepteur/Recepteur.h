#pragma once
#include <avr/io.h>

/**
 * TODO: séparer data de addr et vérifier addr
 */
class Recepteur
{
public:
	Recepteur();
	void ISR_INT_vect();
	void ISR_TIMER_COMP_vect();
	uint8_t isDataReady();
	uint8_t getData();

private:
	void partirMinuterie(uint16_t duree_us);
	void arreterMinuterie();
	void IR_abort();
	void dataReady();
	uint8_t IR_idle;
	uint8_t IR_started;
	uint8_t IR_waiting_data;
	uint8_t IR_data_counter;
	uint8_t IR_data_ready;
	uint8_t IR_wait_timeout;
	uint16_t IR_data;
};