/**
 *
 * @author Louis Racicot & Samuel Rondeau & Feriel Charfeddine & Weiwei
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */
#include "codeBarre.h"
#include "lcd.h"


//tester la couleur blanche
bool readBlanc()
{
	uint8_t	pourcentage = 0;
	//si la valeur lue est entre 120 et 165 ceci correspond au blanc
	for (uint8_t i = 0 ; i < 100; i++)
	{
		if ((PINA & 0x01) == 0x00) {
			pourcentage ++;
		}
	}

	if (pourcentage > 90) {
		return true;
	}
	
	return false;

}

//tester la couleur noir
bool readNoir()
{
	uint8_t	pourcentage = 0;
	//si la valeur lue est entre 200 et 255 ceci correspond au noir
	for (uint8_t i = 0 ; i < 100; i++)
	{
		if ((PINA & 0x01) == 0x01) {
			pourcentage++;
		}
	}

	if (pourcentage > 80) {
		return true;
	}

	return false;
}

uint8_t lireCodeBarre()
{
  enum States {RIEN , DEBUT , BLANC , NOIR};
	States etat;

	uint8_t numItineraire = 0;
	uint8_t q = 0;
	uint8_t dureeBlanc = 0;		//initialiser la variable dureeBlanc.
	uint8_t dureeNoir = 0;		//initialiser la variable dureeNoir.
	uint8_t valeurRetour = 0x00;

	clearLCD();
	etat = RIEN;
	PORTB = 0x00;

	if (readNoir()){
		_delay_ms(20);
		if (readNoir()){
			etat = DEBUT;
			PORTB = 0x02;
		}
	}
	else
		return 0;

	for (uint8_t i = 0 ; i < 7 ; i++)
	{
		switch (etat) {
			case DEBUT:
				while (readNoir()) {
				}

				etat = BLANC;

				break;

			case BLANC:
				PORTB = 0x00;
				dureeBlanc = 0;
				_delay_ms(10);

				while (readBlanc()) {
					_delay_ms(10);
					dureeBlanc++;
				}

				etat = NOIR;

				break;

			case NOIR:
				dureeNoir = 0;
				_delay_ms(10);

				while(readNoir()) {
					_delay_ms(10);
					dureeNoir++;
				}

				if (dureeBlanc < dureeNoir) {
					numItineraire |= 1 << (2-q);
				}

				q++;

				etat = BLANC;

				break;
			case RIEN:
				break;
		}
	}
	writeLCD(numItineraire);
	switch (numItineraire){
		case 0: valeurRetour = 0x0E;
				break;

		case 1: valeurRetour = 0x26;
				break;

		case 2: valeurRetour = 0x52;
				break;
				
		case 3: valeurRetour = 0x1C;
				break;

		case 4: valeurRetour = 0x54;
				break;	

		case 5: valeurRetour = 0x58;
				break;

		case 6: valeurRetour = 0x68;
				break;

		case 7: valeurRetour = 0x70;
				break;	

	}
	
	return valeurRetour;
	
}