/**
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/io.h>
#include "../libpout/src/serial.h"
#include "../libpout/src/sleep.h"
#include "../libpout/src/memoire_24.h"

using namespace libpout;

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

void init()
{
    // Debug led
    DDRA = 0x03;

    initialisationUART();
}

unsigned char USART_Receive( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) )
    ;
    /* Get and return received data from buffer */
    return UDR0;
}

int main()
{
	init();

    PORTA = 0x1;
    msleep(500);
    PORTA = 0x0;

    Memoire24CXXX mem = Memoire24CXXX();

    USART_Receive();
    uint8_t program_size = USART_Receive();

    //unsigned char read;

    for (uint8_t i = 0; i < program_size-2; i++) {
        while ( !(UCSR0A & (1<<RXC0)) ) {
            PORTA = 0x1;
        }
        mem.ecriture(i, UDR0);

        PORTA = 0x2;
        _delay_ms(5);
        PORTA = 0x0;
    }

    return 0; 
}

//001a 0100 