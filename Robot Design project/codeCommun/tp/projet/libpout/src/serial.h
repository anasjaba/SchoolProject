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
	 * This class is used for USB communation using the RS232 protocol.
	 */
	class Serial
	{
		public:
			Serial();

			/**
			 * Send one byte of data to the serial interface.
			 */
			void send(uint8_t data);

		private:
			void init();
	};
}