/**
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include "src/libpout/src/serial.h"
#include "src/libpout/src/memoire_24.h"

 using namespace libpout;

/**
 * The main function. It does the logic.
 */
int main()
{
    DDRA = 0x03;

    Serial usb = Serial();

    Memoire24CXXX mem = Memoire24CXXX();

    uint8_t reading[] = {0};
    mem.lecture(0, reading, 40);


    for (uint8_t i = 0; i < 255; i++ ) {
        usb.send(reading[i]);
    }

    return 0; 
}