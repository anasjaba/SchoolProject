/**
 * According to: http://www.groupes.polymtl.ca/inf1995/tp/tp3/ , 
 * this program turn the LED on to red for a second after the button is pressed 5 times.
 * It can be repeated any number of time.
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-09-19
 * @modified: Look at the SVN
 */

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

bool buttonPressed();
void lightOnRed();
void lightOff();

/**
 * The main function. It does the logic.
 */
int main()
{
    DDRA = 0x03; // Output A
    DDRD = 0x00;

    /**
     * States:
     *    BTN_PRESS1: wait for the first button press
     *    BTN_RELES1: wait for the button to be released
     *    BTN_PRESS2: wait for the second button press
     *    BTN_RELES2: wait for the button to be released
     *    BTN_PRESS3: wait for the third button press
     *    BTN_RELES3: wait for the button to be released
     *    BTN_PRESS4: wait for the 4th button press
     *    BTN_RELES4: wait for the button to be released
     *    BTN_PRESS5: wait for the 5th button press
     *    BTN_RELES5: wait for the button to be released
     *    RED_LIGHT: light on the LED for 1000 ms
     *
     *  Table of truth:
     *   ________________________________________
     *  |ÉTAT PRÉSENT | A | ÉTAT SUIVANT | SORTIE|
     *  |----------------------------------------|
     *  | BTN_PRESS1  | 0 | BTN_PRESS1   |   0   |
     *  | BTN_PRESS1  | 1 | BTN_RELES1   |   0   |
     *  | BTN_RELES1  | 0 | BTN_PRESS2   |   0   |
     *  | BTN_RELES1  | 1 | BTN_RELES1   |   0   |
     *  | BTN_PRESS2  | 0 | BTN_PRESS2   |   0   |
     *  | BTN_PRESS2  | 1 | BTN_RELES2   |   0   |
     *  | BTN_RELES2  | 0 | BTN_PRESS3   |   0   |
     *  | BTN_RELES2  | 1 | BTN_RELES2   |   0   |
     *  | BTN_PRESS3  | 0 | BTN_PRESS3   |   0   |
     *  | BTN_PRESS3  | 1 | BTN_RELES3   |   0   |
     *  | BTN_RELES3  | 0 | BTN_PRESS4   |   0   |
     *  | BTN_RELES3  | 1 | BTN_RELES3   |   0   |
     *  | BTN_PRESS4  | 0 | BTN_PRESS4   |   0   |
     *  | BTN_PRESS4  | 1 | BTN_RELES4   |   0   |
     *  | BTN_RELES4  | 0 | BTN_PRESS5   |   0   |
     *  | BTN_RELES4  | 1 | BTN_RELES4   |   0   |
     *  | BTN_PRESS5  | 0 | BTN_PRESS5   |   0   |
     *  | BTN_PRESS5  | 1 | BTN_RELES5   |   0   |
     *  | BTN_RELES5  | 0 | RED_LIGHT    |   0   |
     *  | BTN_RELES5  | 1 | BTN_RELES5   |   0   |
     *  | RED_LIGHT   | X | BTN_PRESS1   |   1   |
     *  |----------------------------------------|
     */
    enum States {
        BTN_PRESS1,
        BTN_RELES1,
        BTN_PRESS2,
        BTN_RELES2,
        BTN_PRESS3,
        BTN_RELES3,
        BTN_PRESS4,
        BTN_RELES4,
        BTN_PRESS5,
        BTN_RELES5,
        RED_LIGHT
    };

    // Set the initial state
    States state = BTN_PRESS1;

    for(;;) {

        // Check the current state, and do what it should do.
        switch (state) {
            case BTN_PRESS1:
                lightOff();
                if (buttonPressed()) state = BTN_RELES1;
                break;

            case BTN_RELES1:
                if (!buttonPressed()) state = BTN_PRESS2;
                break;

            case BTN_PRESS2:
                if (buttonPressed()) state = BTN_RELES2;
                break;

            case BTN_RELES2:
                if (!buttonPressed()) state = BTN_PRESS3;
                break;

            case BTN_PRESS3:
                if (buttonPressed()) state = BTN_RELES3;
                break;

            case BTN_RELES3:
                if (!buttonPressed()) state = BTN_PRESS4;
                break;

            case BTN_PRESS4:
                if (buttonPressed()) state = BTN_RELES4;
                break;

            case BTN_RELES4:
                if (!buttonPressed()) state = BTN_PRESS5;
                break;

            case BTN_PRESS5:
                if (buttonPressed()) state = BTN_RELES5;
                break;

            case BTN_RELES5:
                if (!buttonPressed()) state = RED_LIGHT;
                break;

            case RED_LIGHT:
                lightOnRed();
                _delay_ms(1000);

                // Return to the initial state
                state = BTN_PRESS1;
                break;

            default:
                break;

        };
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