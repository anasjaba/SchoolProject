/*
 * Nom: Probleme3
 * Copyright (C) 2014 Feriel & Weiwei
 * Description: Tp5 - Probleme3 
 * Version: 1.1
 */

#include <avr/io.h> 
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>


void ajustementPWM ( uint8_t duree  ) {

// mise a un des etat sortie OC1A et OC1B sur comparaison

// reussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe a 0xFF (mode #1 de la table 16-5

// page 135 de la description technique du ATmega324PA)

TCCR1A |= _BV(WGM10)|_BV(COM1A1)|_BV(COM1B1) ;

OCR1A = duree ;

OCR1B = duree ;


// division d'horloge par 8 - implique une frequence de PWM fixe

TCCR1B = _BV(CS11) ;

}



int main()
{
  DDRA = 0xff; 		// PORT A est en mode sortie
  DDRB = 0xff; 		// PORT B est en mode sortie
  DDRC = 0xff; 		// PORT C est en mode sortie
  DDRD = 0xff; 		// PORT D est en mode sortie
                    
  for(;;)  // boucle sans fin
  {
    ajustementPWM ( 0  );
    for(int i = 0; i < 10; i++)
    _delay_ms(200);
    
    ajustementPWM ( 64  );
    for(int i = 0; i < 10; i++)
    _delay_ms(200);
    
    ajustementPWM ( 128  );
    for(int i = 0; i < 10; i++)
    _delay_ms(200);
    
     ajustementPWM ( 191  );
    for(int i = 0; i < 10; i++)
    _delay_ms(200);
    
     ajustementPWM ( 255  );
    for(int i = 0; i < 10; i++)
    _delay_ms(200);
  } 

return 0; 
}

