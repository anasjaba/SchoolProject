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
#pragma once

#include <avr/io.h>

namespace libpout
{
	/**
	 * Represent the output pin for a PWM
	 */
	enum OCR { A0,A1,B1 };

	/**
	 * The class manage the 8 bit PWM capacity of the board for a signle pin
	 * The board can have 2 PWM pin, OCR1A or OCR1B
	 * You shall never instanciate two PWM on the same OCR1,
	 */
	class PWM
	{
		public:

			PWM(){}
			/**
			 * We must specify an output pin (OCR::A0, OCR::A1 or OCR::B1)
			 */
			PWM(OCR port);

			/**
			 * We must specify an output pin (OCR::A0, OCR::A1 or OCR::B1)
			 * and also the initial ratio in 8 bits
			 */
			PWM(OCR port, uint8_t ratio255);

			/**
			 * It adjust the ratio to the specified value
			 */
			void adjust(uint8_t ratio255);

			/**
			 * Start the PWM on Compare Match
			 */
			void start();

			/**
			 * Stop it.
			 */
			void stop();

		private:
			OCR port_;
			void init();
	};
}
