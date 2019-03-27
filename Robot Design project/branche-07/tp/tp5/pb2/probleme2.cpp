/*
 * Nom: Probleme2
 * Copyright (C) 2014 Feriel & Weiwei
 * Description: Tp5 - Probleme2 
 * Version: 1.1
 */

#include <avr/io.h> 
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t minuterieExpiree;
volatile uint8_t boutonPoussoir; 

 void initialisation (void)
{
  cli ();		//bloquer toutes les interruptions
  DDRA = 0xff; 		// PORT A est en mode sortie
  DDRB = 0xff; 		// PORT B est en mode sortie
  DDRC = 0xff; 		// PORT C est en mode sortie
  DDRD = 0x00; 		// PORT D est en mode entree
  EIMSK |= _BV(INT0); 	//ajuster le registre EIMSK
  EICRA |= _BV(ISC00);  //changement de niveau du bouton-poussoir
  sei ();		//recevoir a nouveau des interruptions
  
  
}


ISR ( TIMER1_COMPA_vect   ) {

  minuterieExpiree = 1;

}


ISR ( INT0_vect ) {

  boutonPoussoir = 1;

  // anti-rebond
  _delay_loop_2(65530);
  

}

void partirMinuterie ( uint16_t duree ) {

  minuterieExpiree = 0;

// mode CTC du timer 1 avec horloge divisee par 1024

// interruption après la duree specifiee

TCNT1 = 0x0000 ;

OCR1A = duree;

TCCR1A |= _BV(WGM12)|_BV(COM1A0)|_BV(COM1B0) ;

TCCR1B = _BV(CS12)|_BV(CS10) ;

TIMSK1 |= _BV(OCIE1A)|_BV(OCIE1B);

}

int main()
{
  
  initialisation ();                      
 // for(;;)  // boucle sans fin
 // {
  for(int i = 0; i < 100; i++)
    _delay_ms(100);
  
  PORTA = 0x02;
  _delay_ms(100);
  PORTA = 0x00;
  
  partirMinuterie(7812);
  do {

// attendre qu'une des deux variables soit modifiée

// par une ou l'autre des interruptions.
    

  } while ( minuterieExpiree == 0 && boutonPoussoir == 0 );


// Une interruption s'est produite. arreter toute

// forme d'interruption. Une seule reponse suffit.

  cli ();

// Verifier la reponse

  if(minuterieExpiree == 0 && boutonPoussoir == 1)
    PORTA = 0x01;
  else if ( minuterieExpiree == 1 )
    PORTA = 0x02;
  else
        {}
    

return 0; 
}

