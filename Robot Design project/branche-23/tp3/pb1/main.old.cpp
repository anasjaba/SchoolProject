#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

bool buttonPressed();

int main()
{
    DDRA = 0x03; // Output A
    DDRD = 0x00;

    // Number of button press
    uint8_t counter = 0;

    for(;;) {

        // If the button is being pressed
        if (buttonPressed()) {

            // Wait unil it's unpressed
            while (buttonPressed()) {
                _delay_ms(10);
            }

            // Then increment the pressed counter
            counter++;
        }

        // If the button has been pressed 5 time, light on the LED for 1000 ms
        if (counter == 5) {
            // And reset the counter
            counter = 0;
            PORTA = 0x1;
            _delay_ms(1000);
            PORTA = 0x0;
        }
    }

    return 0; 
}

/**
 * This function gives the state of the button: Is it being pressed or not ?
 */
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