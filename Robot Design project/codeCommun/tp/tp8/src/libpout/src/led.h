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
	 * Represent a port on the board.
	 */
	enum Ports { A,B,C,D };

	/**
	 * The class represent a Bi-Color LED. It can be red, green or off.
	 */
	class led
	{
		public:
			/**
			 * We must specify a port (Ports::A, Ports::B, Ports::C or Ports::D)
			 * and the two pins (0..7) on which the wires are plugged.
			 */
			led(Ports port, uint8_t pin1, uint8_t pin2);

			/**
			 * Light on the LED with the red color.
			 * If it turn on green with this method, switch the wires, you idiot.
			 */
			void lightOnRed();

			/**
			 * Light on the LED with the green color.
			 * If it turn on red with this method, switch the wires, you idiot.
			 */
			void lightOnGreen();

			/**
			 * Light off the LED
			 * If it doesn't light off with this method, what the fuck have done?
			 */
			void lightOff();

		private:
			Ports port_;
			uint8_t pin1_;
			uint8_t pin2_;
	};
}