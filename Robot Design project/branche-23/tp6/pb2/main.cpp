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

void initialisationUART(void)
{
	// 2400 bauds. Nous vous donnons la valeur des deux
	// premier registres pour vous éviter des complications
	UBRR0H = 0;
	UBRR0L = 0xCF;

	// permettre la reception et la transmission par le UART0
	UCSR0A = _BV(UDRE0);//_BV(RXC0) | _BV(TXC0);
	UCSR0B = _BV(RXEN0)| _BV(TXEN0);

	// Format des trames: 8 bits, 1 stop bits, none parity
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

void transmissionUART( uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

/**
 * The main function. It does the logic.
 */
int main()
{
	initialisationUART();
    char mots[21] = "Le robot en INF1995\n";

	uint8_t i, j;
	for ( i = 0; i < 100; i++ ) {
		for ( j=0; j < 20; j++ ) {
			transmissionUART ( mots[j] );
		}
	}

    return 0; 
}