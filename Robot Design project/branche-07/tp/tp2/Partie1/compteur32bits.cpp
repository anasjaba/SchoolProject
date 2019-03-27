/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */


#include <avr/io.h>
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0xff; // PORT D est en mode sortie
 // unsigned long compteur=0; // le compteur est initialise a 0.
                            // c'est un compteur de 32 bits

 
  for(;;)  // boucle sans fin
  {
    PORTB = 0x01;
    _delay_ms(3000);
    PORTB = 0x02;
    _delay_ms(3000);
    for (unsigned int i = 0; i < 3000 ;i++ )
      {
	 PORTB = 0x01;
	 _delay_ms(0.5);
	 PORTB = 0x02;
	_delay_ms(0.5);
	
      }
      
  }
}

