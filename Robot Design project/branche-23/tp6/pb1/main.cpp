/**
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "memoire_24.h"

void lightOnRed();
void lightOnGreen();
void lightOff();

/**
 * The main function. It does the logic.
 */
int main()
{
    DDRA = 0x03;

    Memoire24CXXX mem = Memoire24CXXX();

    uint8_t str[] = "*E*C*O*L*E* *P*O*L*Y*T*E*C*H*N*I*Q*U*E*\0";

    mem.ecriture(0, str, 40);
    _delay_ms(10);

    uint8_t reading[] = {0};

    mem.lecture(0, reading, 40);

    uint8_t comp = 0;

    for (uint8_t i = 0; i < 40; i++ ) {
        if (reading[i] != str[i]) {
            comp = 1;
        }
    }

    if (!comp) {
    	for(;;)
    		lightOnGreen();
    } else {
    	for(;;)
			lightOnRed();
    }

    return 0; 
}

/**
 * Light on the LED in red
 */
void lightOnRed()
{
    PORTA = 0x1;

}

/**
 * Light on the LED in green
 */
void lightOnGreen()
{
    PORTA = 0x2;
}

/**
 * Light off the LED
 */
void lightOff()
{
    PORTA = 0x0;
}