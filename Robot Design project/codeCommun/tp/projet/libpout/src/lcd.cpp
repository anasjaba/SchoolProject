#include "lcd.h"

void static inline w(void) {
	cp_wait_ms(2000);
}

void writeLCD(uint8_t val) 		
{

	// Création de l'objet (l'afficheur est connecté sur le port DEMO_PORT)
	LCM disp(&DDRC, &PORTC);

	//nettoyer l'afficheur
	disp.clear();

	//afficher 6 caractères espace
	for (uint8_t i = 0 ; i < 7 ; i++) {
		disp.put(' ');
	}

	//afficher le numero d'itinéraire
	disp << val ;
	w();
}

void clearLCD()
{
	// Création de l'objet (l'afficheur est connecté sur le port DEMO_PORT)
	LCM disp(&DDRC, &PORTC);

	//nettoyer l'afficheur
	disp.clear();
}