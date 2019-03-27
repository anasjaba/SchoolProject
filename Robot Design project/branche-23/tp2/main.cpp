#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

bool buttonPressed();

int main()
{
    DDRA = 0xff; // Output A
    DDRD = 0x00;

    for(;;) {

        while(buttonPressed()) {
            PORTA = 0x1;
            _delay_ms(10);
            PORTA = 0x2;
            _delay_ms(10);
        }

        PORTA = 0x00;
    }

    return 0; 
}

bool buttonPressed()
{
    if ( PIND & 0x04 ) {
        _delay_ms(10);

        if ( PIND & 0x04 ) {
            return true;
        }
    } else {
        _delay_ms(10);

        if ( PIND & 0x04 ) {
            return buttonPressed();
        }
    }

    return false;
}