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

/**
 * The main function. It does the logic.
 */
 int main()
{
    DDRA = 0x03; // Output A
    DDRD = 0x00;

    /**
     * States:
     *    RST_RED:      The light is red until button press
     *    AMB_GREEN:    The light is green in amber sequence until button release
     *    AMB_RED:      The light is red in amber sequence until button release
     *    GREEN1:       The light is green until button press
     *    RED:          The light is red until button release
     *    OFF:          The light is off until button press
     *    GREEN2:       The light is green until button release
     *
     *  Table of truth:
     *   _________________________________________
     *  |ÉTAT PRÉSENT | A | ÉTAT SUIVANT | SORTIE |
     *  |-----------------------------------------|
     *  | RST_RED     | 0 | RST_RED      |   01   |
     *  | RST_RED     | 1 | AMB_GREEN    |   01   |
     *  | AMB_GREEN   | 0 | GREEN1       |   10   |
     *  | AMB_GREEN   | 1 | AMB_RED      |   10   |
     *  | AMB_RED     | 0 | GREEN1       |   01   |
     *  | AMB_RED     | 1 | AMB_GREEN    |   01   |
     *  | GREEN1      | 0 | GREEN1       |   10   |
     *  | GREEN1      | 1 | RED          |   10   |
     *  | RED         | 0 | OFF          |   01   |
     *  | RED         | 1 | RED          |   01   |
     *  | OFF         | 0 | OFF          |   00   |
     *  | OFF         | 1 | GREEN2       |   00   |
     *  | GREEN2      | 0 | RST_RED      |   10   |
     *  | GREEN2      | 1 | GREEN2       |   10   |
     *  |-----------------------------------------|
     */
    enum States {
        RST_RED,
        AMB_GREEN,
        AMB_RED,
        GREEN1,
        RED,
        OFF,
        GREEN2
    };

    // Set the initial state
    States state = RST_RED;

    for(;;) {

        // Check the current state, and do what it should do.
        switch (state) {
            case RST_RED:
                lightOnRed();
                if (buttonPressed()) state = AMB_GREEN;
                break;

            case AMB_GREEN:
                lightOnGreen();
                (buttonPressed() ? state = AMB_RED : state = GREEN1);
                break;

            case AMB_RED:
                lightOnRed();
                (buttonPressed() ? state = AMB_GREEN : state = GREEN1);
                break;

            case GREEN1:
                lightOnGreen();
                if (buttonPressed()) state = RED;
                break;

            case RED:
                lightOnRed();
                if (!buttonPressed()) state = OFF;
                break;

            case OFF:
                lightOff();
                if (buttonPressed()) state = GREEN2;
                break;

            case GREEN2:
                lightOnGreen();
                if (!buttonPressed()) state = RST_RED;
                break;

            default:
                lightOnRed();
                break;

        };
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