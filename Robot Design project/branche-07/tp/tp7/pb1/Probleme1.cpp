/***************************************
 * Nom: Probleme1 
 * Copyright (C) 2014 Feriel & Weiwei
 * Description: Tp7 - Probleme1 
 * Version: 1.1
 ***************************************/

/********************************************************************************************
 * Nous avons relié les fils brun-bleu aux PORTD : fil Bleu lié au PD3 et le Brun non relié
 * Nous avons relié la LED au PORTA: LED A1-A2
 * Nous avons relié les fils rouge-noir au PORTB : Rouge lié au VCC et Noir lié au GND
 * ****************************************************************************************/

#include <avr/io.h> 
#define F_CPU 8000000UL // 1 MHz
#include <util/delay.h>
unsigned int compteur = 0; 				// le compteur est initialise a 0, on le déclare comme une variable globale 

/*******************************************************
*Fonction: verifierButton()
*Description: une fonction pour vérifier si le bouton est enfoncé ou relâché et faire un anti rebont
*Parametres: auncun
*Valeur de retour: une valeur booléenne 
*******************************************************/
bool verifierButton()	
{
  bool valeur = false;
   if (!(PIND & 0x04)) 					//vérifier si on appuie sur le bouton poussoir(logique inverse)
	{
	   _delay_ms(10);				//attendre 10ms pour éviter le rebont
	   if (!(PIND & 0x04)) 
	    valeur = true;
	}
    return valeur;
   
}

/*******************************************************
*Fonction: clignoteRouge(unsigned int compteur)
*Description: une fonction pour faire clignoter la lumière rouge
*Parametres: unsigned int
*Valeur de retour: aucun
*******************************************************/
void clignoteRouge(unsigned int compteur)	
{
  unsigned int nbClignotements;
  do
  {
    PORTA = 0x02;				//LED A1-A2 s'allume en rouge
    _delay_ms(250);   				//pendant 250 ms
    PORTA = 0x00;				//LED A1-A2 s'éteint
    _delay_ms(250);				//pendant 250 ms 
    nbClignotements ++;				//incrémenter le nombre de clignotements (on aura donc deux clignotements par seconde)
  }
  while(nbClignotements <= compteur/2);
  
}
/*******************************************************
*Fonction: clignoteVert()
*Description: une fonction pour faire clignoter la lumière vert
*Parametres: aucun
*Valeur de retour: aucun
*******************************************************/

void clignoteVert()			
{
    for( unsigned int i = 0; i < 5; i++)	//pendant une demie seconde, la lumiere clignote en vert
    {
      PORTA = 0x01;				//LED A1-A2 s'allume en vert
      _delay_ms(100);				//attendre 100 ms
      PORTA = 0x00;				//LED A1-A2 s'éteint
    }
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie 
  DDRB = 0x00; // PORT B est en mode entree
  DDRC = 0x00; // PORT C est en mode entree
  DDRD = 0x00; // PORT D est en mode entree
 
 for (;;)
 {
  if (verifierButton()) 					//vérifier si on appuie sur le bouton poussoir	
    {
      while(!(PIND & 0x04) && compteur < 120)		//tant que le bouton est enfoncé et le compteur est inférieur à 120
	{
	  _delay_ms(100);				//chaque 100 ms 
	  compteur++;					//le compteur s'incrémente  (pour avoir 10 imcrémentations en 1 seconde)
	}
    
      if (!(verifierButton()) || compteur == 120)	//si on relache le bouton ou si le compteur atteint 120
      {
	clignoteVert();					//on fait appel a la fonction clignoteVert()
	PORTA = 0x00;					//la LED A1-A2 passe à l'état éteint
	for (unsigned int j = 0; j < 20; j++)		//pendant 2 secondes
	  _delay_ms(100);
    
	clignoteRouge(compteur);			//après 2 secondes, on fait appel à la fonction de clignote rouge
	PORTA = 0x01;					//LED A1-A2 s'allume en vert
	for( unsigned int i = 0; i < 10; i++)		//pendant une seconde 
	  _delay_ms(100);
    
	PORTA = 0x00;					//LED A1-A2 s'éteint
	compteur = 0;					//remettre le compteur a zéro
      }
    }
 }
  return 0; 
}
