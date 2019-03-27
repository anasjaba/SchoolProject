/*
 * Nom: Probleme2
 * Copyright (C) 2014 Feriel & Weiwei
 * Description: Tp3 - Probleme2 
 * Version: 1.1
 */

/*
  Tableau des états:
  Etat Présent| Entrée A| Etat suivant| Z | Y       sortie X et Y representent la couleur de la LED donc : Eteint = 00
  INIT        |  0      |   INIT      | 1 | 0								     Vert =  01
  INIT        |  1      |   AMBRE     | 1 | 0								     Rouge = 10
  AMBRE       |  1      |   AMBRE     | 1 | 1								     Ambre = 11
  AMBRE       |  0      |   VERT1     | 1 | 1	
  VERT1       |  0      |   VERT1     | 0 | 1	 	L'entree A represente le bouton poussoir  : Enfonce = 1
  VERT1       |  1      |   ROUGE     | 0 | 1							    Relache = 0
  ROUGE       |  1      |   ROUGE     | 1 | 0
  ROUGE       |  0      |   ETEINT    | 1 | 0
  ETEINT      |  0      |   ETEINT    | 0 | 0
  ETEINT      |  1      |   VERT2     | 0 | 0
  VERT2       |  1      |   VERT 2    | 0 | 1
  VERT2       |  0      |   INTI      | 0 | 1
  
  
  
  
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
  enum Etats  {INIT, AMBRE, VERT1, ROUGE , ETEINT, VERT2};
  Etats etat = INIT;
                           
  for(;;)  // boucle sans fin
  {
     switch (etat) 
      {
	case INIT:				//si c'est l'état initial
	 
		PORTA = 0x02;			//allumer la LED en rouge
		if (PIND & 0x04) 		//vérifier si on appuie sur le bouton poussoir
		{
		  _delay_ms(10);		//attendre 10ms pour éviter le rebont
		    if (PIND & 0x04) 
		      etat = AMBRE;		//passer a l'etat AMBRE
		}
		  
		
	  break;
	 
	case AMBRE :
	
	  while (PIND & 0x04)			//boucle pour la couleur AMBRE
	    {	PORTA = 0x02;
	        _delay_ms(10);
	        PORTA = 0x01;
	        _delay_ms(10);
	    }
	     if (PIND == 0x00)			//si on relache le bouton poussoir
	      etat = VERT1;			//on passe a l'etat VERT1
	  
	  break;
	  
	case VERT1 : 
	
	  PORTA = 0x01;				//allumer la LED en vert
	  if (PIND & 0x04) 			//vérifier si on appuie sur le bouton poussoir
		{
		  _delay_ms(10);		//attendre 10ms pour éviter le rebounce
		    if (PIND & 0x04) 
		      etat = ROUGE;  		//on passe a l'etat ROUGE
		}
		
	break;
	
	case ROUGE : 
	   PORTA = 0x02;			//allumer la LED en rouge
	   if (PIND == 0x00)			//si on relache le bouton poussoir
	      etat = ETEINT;			//on passe a l'etat ETEINT
	   break;
	   
	 case ETEINT : 
	   PORTA = 0x00;			//on eteint la LED
	    if (PIND & 0x04) 			//vérifier si on appuie sur le bouton poussoir
		{
		  _delay_ms(10);		//attendre 10ms pour éviter le rebounce
		    if (PIND & 0x04) 
		      etat = VERT2;		//On passe a l'etat VERT2
		}
	     
	   break;
	   
	 case VERT2 : 
	   PORTA = 0x01;			//allumer la LED en vert
	    if (PIND == 0x00)			//si on relache le bouton poussoir
	      etat = INIT;			// on revient a l'etat INIT
     
	   break;
	   
	   default:
	      break;
      }   
  }
  return 0; 
}


