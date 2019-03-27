/*
 * Nom: Probleme1
 * Copyright (C) 2014 Feriel & Weiwei
 * Description: Tp3 - Probleme1 
 * Version: 1.1
 */

/*
  Tableau des états:
  Etat Présent| Entrée A| Etat suivant| Sortie Z
  INIT        |  0      |   INIT      | 0
  INIT        |  1      |   TRANS     | 0
  TRANS       |  0      |   TRANS     | 0
  TRANS       |  1*     |   TRANS     | 0	 *4 FOIS OU MOINS
  TRANS       |  1*     |   FIN       | 0	 * 5 EME APPUI
  FIN         |  X      |   INIT      | 1 
  
*/
#include <avr/io.h> 
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>


int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRB = 0xff; // PORT B est en mode sortie
  DDRC = 0xff; // PORT C est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  unsigned int compteur=0; 	// le compteur est initialise a 0
  enum Etats  {INIT, TRANSITION, FIN};
  Etats etat = INIT;
                           
  for(;;)  // boucle sans fin
  {
     switch (etat) 
      {
	case INIT:			//si c'est l'état initial
	 
		PORTA = 0x00;
		etat = TRANSITION;	//on passe a l'etat TRANSITION
	
	  break;
	 
	case TRANSITION :
	
	  if (PIND & 0x04) 		//vérifier si on appuie sur le bouton poussoir
	  {
	      _delay_ms(10);		//attendre 10ms pour éviter le rebounce
	      if (PIND & 0x04) 
	      {
		etat = TRANSITION;
	      }
		if (PIND == 0x00) 	//Lorsqu'on elache le bouton poussoir
		{
		  compteur ++;		//incrementer le compteur
		}
		
	      }
	      
		
	   if(compteur == 5)		//Lorsque le compteur atteint 5 appuis
		{
		  etat = FIN;		//on passe a l'etat FIN
		  compteur = 0;		//remettre le compteur a zero
		}
	   
	  
	  break;
	  
	case FIN : 
	
	  PORTA = 0x02;			//allumer la LED en rouge
	  _delay_ms(1000);		//pendant 1 seconde
	  PORTA = 0x00;			//eteindre la LED
	  etat = INIT;			//revenir a l'etat INIT
	break;				
	
	default:
	  break;
	  
      }   
  }
  return 0; 
}



