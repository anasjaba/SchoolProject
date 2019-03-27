/*
 * Nom: tp4_probleme1
 * Copyright (C) 2014 
 * License http:
 * Description: 
 */


#include <avr/io.h>
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>

void delai(unsigned int x)
{
  for(unsigned int j = x; j > 0; j--)
  {
   //_delay_us(30);
   _delay_loop_2(2);
  }
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entrée

unsigned int x = 1000;
 
  for(;;)  // boucle sans fin
  {

    for (unsigned int i = 0; i < 3000 ; i++ )
    {
      PORTA = 0x02;
      delai(x);
       PORTA = 0x00;
      delai(1000 - x);
      if (i%3 == 0)
	x--;
      
    }
    x=1000;
  }
  return 0;
}
