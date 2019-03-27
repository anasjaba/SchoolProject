/**
 * According to: http://www.groupes.polymtl.ca/inf1995/tp/tp3/ , 
 * this program turn the LED on and off with a predefined sequence of color.
 * The sequence can be repeated any number of time.
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-09-19
 * @modified: Look at the SVN
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

bool buttonPressed();
void lightOnGreen();
void lightOnRed();
void lightOff();
void usleep(int us);

/**
 * The main function. It does the logic.
 */
 int main()
{
    DDRA = 0x03; // Output A
    DDRD = 0x00;

    /**
     * States:
     *    ON:    The light is red
     *    OFF:   The light is off
     *    DECAY: The light is red and dim for 3 sec.
     *
     *  Table of truth:
     *   _________________________________________
     *  |ÉTAT PRÉSENT | A | ÉTAT SUIVANT | SORTIE |
     *  |-----------------------------------------|
     *  | ON          | 0 | DECAY        |   01   |
     *  | ON          | 1 | ON           |   01   |
     *  | OFF         | 0 | OFF          |   00   |
     *  | OFF         | 1 | ON           |   00   |
     *  | DECAY       | 0 | OFF          |   xx   |
     *  | DECAY       | 1 | OFF          |   xx   |
     *  |-----------------------------------------|
     */
    enum States {
        OFF,
        ON,
        DECAY
    };

    // Set the initial state
    States state = OFF;
    int a, b;

    for(;;) {

        // Check the current state, and do what it should do.
        switch (state) {
            case OFF:
            lightOff();
                if (buttonPressed()) state = ON;
                break;

            case ON:
            lightOnRed();
                if (!buttonPressed()) state = DECAY;
                break;

            case DECAY:
                a = 1000;
                b = 0;
                for(int i = 0; i < 3000; i++){
                    lightOnRed();
                    usleep(a);
                    lightOff();
                    usleep(b);

                    if (!(i%3)) {
                        a--;
                        b++;
                    }
                }
                state = OFF;
                break;

            default:
                state = OFF;
                break;
        }
    }

    return 0; 
}

/**
 * Light on the LED in green
 */
void lightOnGreen()
{
    PORTA = 0x2;
}

/**
 * Light on the LED in red
 */
void lightOnRed()
{
    PORTA = 0x1;
}

/**
 * Light off the LED
 */
void lightOff()
{
    PORTA = 0x0;
}

/**
 * This function gives the state of the button: Is it being pressed or not ?
 */
bool buttonPressed()
{
    // If the button is pressed
    if ( PIND & 0x04 ) {
        _delay_ms(10);

        // If it still pressed after 10 ms
        if ( PIND & 0x04 ) {

            // Yup, that's a real press
            return true;
        }
    } else {
        _delay_ms(10);

        // If the button wasn't pressed, but it is after 10 ms, we should check if it's a "real" press
        if ( PIND & 0x04 ) {
            return buttonPressed();
        }
    }

    // We are now sure that the button is not pressed.
    return false;
}

void usleep(int us) {
    for(int i = 0; i < us/3; i++){
        _delay_loop_2(4);
    }
}