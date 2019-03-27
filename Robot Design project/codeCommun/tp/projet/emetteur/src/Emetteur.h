#pragma once
#include <avr/io.h>
#include "../../libpout/src/pwmIrc.h"
using namespace libpout;

class Emetteur{
public:
	Emetteur();

	void start();
	void stop();
	void sendSequence(const uint8_t message);
	void sendSequence(const uint8_t message, const uint8_t n);

private:
	pwmIrc pwm;
	void pulse(uint8_t bit, uint8_t& nbT);
	void wait(uint8_t& nbT);
	void signalStart(uint8_t& nbT);
};