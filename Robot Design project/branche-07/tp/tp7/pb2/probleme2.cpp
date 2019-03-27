/***************************************
 * Nom: Probleme2 
 * Copyright (C) 2014 Feriel & Weiwei
 * Description: Tp7 - Probleme2 
 * Version: 1.1
 ***************************************/

/********************************************
 * On relie les fils rouge et noir avec le PORTA: le rouge est relié au Vcc et le noir est relié au Gnd
 * Les fils brun et bleu sont relié au PORTA: seulement le bleu est relié à la broch A1 le brun est libre
 * La Led est reliée au PORTB : B1-B2
 * ******************************************/

#include "can.cpp"
#include <avr/io.h> 
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>

int main()
{ 
  
  DDRA = 0x00; // PORT A est en mode entree 
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0x00; // PORT C est en mode entree
  DDRD = 0x00; // PORT D est en mode entree
  
  can convertisseur;
  const  uint16_t puissanceMin = 77 ;		//puissance à 30%
  const  uint16_t puissanceMoyenne = 205 ;	//puissance à 80%
  const  uint16_t puissanceMax = 255 ;		//puissance à 100%
  enum etats {ROUGE, VERT, AMBRE};
  etats etat;
  
  for (;;)
  {
  uint16_t puissance = convertisseur.lecture(0) ;
  puissance = puissance >> 0x2;
  
  if (puissance >= 0 && puissance < puissanceMin )
    etat = VERT;
    
  if (puissance >= 77 && puissance < puissanceMoyenne )
    etat = AMBRE;
  
  if (puissance >= puissanceMoyenne && puissance < puissanceMax)
     etat = ROUGE;
   
  switch (etat)
    {
  
      case VERT:				//si la puissance est à inférieur 30%
	PORTB = 0x01;				//le led B1-B2 s'allume en vert
	break;
    
    case AMBRE:					//si la puissance est inférieure à 80%
      for (uint16_t i = 0; i<20 ; i++)		//boucle pour la couleur ambrée
      {
	PORTB = 0x02;				//led B1-B2
	_delay_ms(10);
	PORTB = 0x01;
	_delay_ms(10);
      }
      break;
	
    case ROUGE:					//si la puissance est supérieure à 80%
      PORTB = 0x02;				//led B1-B2 s'allume en rouge
      break;
      
     default:
      break;
    }
  }
    
  return 0;
}
