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

void engineOn();
void engineOff();
void usleep(int us);
void msleep(double ms);

/**
 * The main function. It does the logic.
 */
 int main()
{
    DDRC = 0x03; // Output A
    DDRD = 0x00;

    /**
     * States:
     *    ON:    The engine is on
     *    OFF:   The engine is off
     *
     *  Table of truth:
     *   _________________________________________
     *  |ÉTAT PRÉSENT | A | ÉTAT SUIVANT | SORTIE |
     *  |-----------------------------------------|
     *  | ON          | 0 | OFF          |   xx   |
     *  | ON          | 1 | OFF          |   xx   |
     *  | OFF         | 0 | OFF          |   00   |
     *  | OFF         | 1 | OFF          |   00   |
     *  |-----------------------------------------|
     */
    enum States {
        OFF,
        ON
    };

    // Set the initial state
    States state = ON;
    double a, b;

    for(;;) {

        // Check the current state, and do what it should do.
        switch (state) {
            case OFF:
            engineOff();
                break;

            case ON:
                // 60 Hz

                a = 0.0;
                b = 16.0;

                for(int i = 1; i < 601; i++){
                    engineOn();
                    msleep(a);
                    engineOff();
                    msleep(b);

                    if (!(i%120)) {
                        a += 4.0;
                        b -= 4.0;
                    }
                }

                // 400 Hz

                a = 0;
                b = 2.5;

                for(int i = 1; i < 4001; i++){
                    engineOn();
                    msleep(a);
                    engineOff();
                    msleep(b);

                    if (!(i%800)) {
                        a += 0.625;
                        b -= 0.625;
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
 * Power on the engine
 */
void engineOn()
{
    PORTC = 0x03;
}

/**
 * Poweroff the engine
 */
void engineOff()
{
    PORTC = 0x00;
}

void usleep(int us) {
    for(int i = 0; i < us/3; i++){
        _delay_loop_2(4);
    }
}

void msleep(double ms) {
    int us = ms * 1000;
    usleep(us);
}