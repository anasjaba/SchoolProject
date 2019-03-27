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
#include <avr/interrupt.h>
#include <util/delay.h>

bool buttonPressed();
void lightOnGreen();
void lightOnRed();
void lightOff();

enum States {
    RST_RED,
    AMB,
    GREEN1,
    RED,
    OFF,
    GREEN2
};

// Set the initial state
volatile States state = RST_RED;

ISR (INT0_vect) {
    uint8_t bouton = (PIND & 0x4);
    
    // laisser un delai avant de confirmer la reponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_loop_2 ( 65530 );

    // Se souvenir ici si le bouton est presse ou relache
    if(bouton == (PIND & 0x4)) {
        // changements d'etats tels que ceux de la
        // semaine precedente
        if (state == GREEN2) {
            state = RST_RED;
        } else {
            state = (States) ((int)state + 1);
        }
    }
    // Voir la note plus bas pour comprendre cette instruction et son role
    EIFR |= (1 << INTF0);
}

void initialisation ( void ) {
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'etre interrompu alors que
    // le microcontroleur n'est pas pret...
    cli ();

    // configurer et choisir les ports pour les entrees
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA = 0x03; // Output A
    DDRD = 0x00;

    // cette procédure ajuste le registre EIMSK
    // de ATmega324PA pour permettre les interruptions externes
    EIMSK |= _BV(INT0);

    // il faut sensibiliser les interruptions externes aux
    // changement de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= 00000001;

    // sei permet de recevoir a nouveau des interruptions.
    sei ();
}


/**
 * The main function. It does the logic.
 */
int main()
{
    initialisation();

    /**
     * States:
     *    RST_RED:      The light is red
     *    AMB:          The light is amber
     *    GREEN1:       The light is green 
     *    RED:          The light is red 
     *    OFF:          The light is off
     *    GREEN2:       The light is green
     */

    for(;;) {

        // Check the current state, and do what it should do.
        switch (state) {
            case RST_RED:
                lightOnRed();
                break;

            case AMB:
                lightOnGreen();
                _delay_ms(10);
                lightOnRed();
                _delay_ms(10);
                break;

            case GREEN1:
                lightOnGreen();
                break;

            case RED:
                lightOnRed();
                break;

            case OFF:
                lightOff();
                break;

            case GREEN2:
                lightOnGreen();
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