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

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir;

ISR (TIMER1_COMPA_vect) {
    minuterieExpiree = 1;
}

ISR (INT0_vect) {
    boutonPoussoir = 1;
    
    // laisser un delai avant de confirmer la reponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_loop_2 ( 65530 );

    // Se souvenir ici si le bouton est presse ou relache

    // Voir la note plus bas pour comprendre cette instruction et son role
    EIFR |= (1 << INTF0);
}

void partirMinuterie ( uint16_t duree ) {
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisee par 1024
    // interruption après la duree specifiee
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    TCCR1B |= _BV(WGM12) | _BV(CS12) | _BV(CS10); // 00001101; WGM12 = CTC mode, 
    TIMSK1 |= _BV(OCIE1A); //00000010;
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
    EICRA |= _BV(ISC01) | _BV(ISC00);

    // sei permet de recevoir a nouveau des interruptions.
    sei ();
}


/**
 * The main function. It does the logic.
 */
int main()
{
    initialisation();

    _delay_ms(1000);
    lightOnRed();
    _delay_ms(100);
    lightOff();

    partirMinuterie(7812);
    //minuterieExpiree = 1;

    do {
    // attendre qu'une des deux variables soit modifiée
    // par une ou l'autre des interruptions.
    
    } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );
    
    // Une interruption s'est produite. arreter toute
    // forme d'interruption. Une seule reponse suffit.
    cli ();
    
    // Verifier la reponse
    if ( minuterieExpiree == 1 ) {
        for(;;) {
            lightOnRed();
        }
    } else {
        for(;;) {
            lightOnGreen();
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