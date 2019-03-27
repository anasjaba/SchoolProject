/**
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#define debug true
#include <avr/io.h>
#include "../../libpout/src/serial.h"
#include "../../libpout/src/pwm.h"
#include "../../libpout/src/sleep.h"
#include "can.h"


#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupé par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupé par l'afficheur

void static inline w(void) {
	cp_wait_ms(2000);
}

using namespace libpout;

Serial usb;
uint8_t dureeBlanc = 0;		//initialiser la variable dureeBlanc.
uint8_t dureeNoir = 0;		//initialiser la variable dureeNoir.


void init()
{
	DDRA = 0x00;
	DDRB = 0xFF;

	if (debug) {
		usb = Serial();
	}
}

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

void writeLCD(uint8_t val) 		
{

	// Création de l'objet (l'afficheur est connecté sur le port DEMO_PORT)
	LCM disp(&DEMO_DDR, &DEMO_PORT);

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


/**
 * The main function. It does the logic.
 */
 int main()
 {
	init();

	PORTB = 0x02;
	_delay_ms(1000);

	enum States {RIEN , DEBUT , BLANC , NOIR};
	States etat;

	uint8_t numItineraire = 0;
	uint8_t q = 0;

	while (!readNoir())
	{
		etat = RIEN;
		PORTB = 0x00;
	}

	etat = DEBUT;

	for (uint8_t i = 0 ; i < 7 ; i++)
	{
		switch (etat) {
			case DEBUT:
				while (readNoir()) {
					PORTB = 0x02;	
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
				PORTB = 0x01;
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
				usb.send(dureeBlanc);
				usb.send(dureeNoir);

				break;
			case RIEN:
				break;
		}
	}

	writeLCD(numItineraire) ;

	return 0; 
}