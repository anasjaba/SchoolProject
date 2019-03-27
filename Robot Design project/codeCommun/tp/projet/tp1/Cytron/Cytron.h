#pragma once
#include <avr/io.h>

class Cytron{
public:
	Cytron();
	void refresh();

	bool getSenseur(uint8_t i);

private:
	bool senseurs[5] = {false, false, false, false, false};
};