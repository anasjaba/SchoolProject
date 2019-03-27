/**
 * According to: http://www.groupes.polymtl.ca/inf1995/tp/tp3/ , 
 * this program turn the LED on and off with a predefined sequence of color.
 * The sequence can be repeated any number of time.
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-09-19
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*void partirMinuterie ( uint16_t duree ) {
    minuterieExpiree = 0;
    // mode CTC du timer 1 avec horloge divisee par 1024
    // interruption après la duree specifiee
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= _BV(COM1A1) | _BV(COM1A0);
    TCCR1B |= 00001101;
    TIMSK1 |= 00000010;
}*/

void ajustementPWM ( uint8_t ratio255 ) {
    // mise a un des etat sortie OC1A et OC1B sur comparaison
    // reussie en mode PWM 8 bits, phase correcte
    // et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5
    // page 135 de la description technique du ATmega324PA)
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1A0) | _BV(COM1B0) | _BV(WGM10);
    OCR1A = ratio255;
    OCR1B = ratio255;

    // division d'horloge par 8 - implique une frequence de PWM fixe
    TCCR1B = _BV(CS11);
}


/**
 * The main function. It does the logic.
 */
int main()
{
    DDRD = 0xFF;
    TCNT1 = 0;

    ajustementPWM(0);
    _delay_ms(2000);
    ajustementPWM(64);
    _delay_ms(2000);
    ajustementPWM(128);
    _delay_ms(2000);
    ajustementPWM(191);
    _delay_ms(2000);
    ajustementPWM(255);
    _delay_ms(2000);

    return 0; 
}