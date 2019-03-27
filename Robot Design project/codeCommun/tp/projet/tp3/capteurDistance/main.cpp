#define F_CPU 8000000UL
#define vitesse 140
#include <avr/io.h>
//#include "Cytron.h"
#include "../../libpout/src/serial.h"
#include "../../libpout/src/sleep.h"
#define debug true
#include "MoteurManager.h"
//#include "distanceSensor.h"
#include "can.h"

using namespace std;

Serial usb;

void init()
{
	// Port A en lecture
	DDRA = 0x00;
	DDRC = 0x00;

	// PWM output for engines
	DDRD = 0x3C; // OCR1A, OCR1B

	if (debug) {
		usb = Serial();
	}
}

bool detecter(uint8_t limite)
{
	uint8_t nbDetection = 0;				//nombre de détection effectuées par le capteur
				
	for (uint8_t i = 0; i < 100 ; i++)
	{
	  can conv = can();						//construire un can pour traduire le signale reçu par le capteur
	  if ((conv.lecture(0) >> 2) > limite)	//si la valeur retournée par le can est supérieure à 10
	    nbDetection ++;						//incrémenter le nombre d'intersection
	    _delay_ms(2);
	}
	usb.send(nbDetection);
	if (nbDetection > 85)					//si 85% des valeurs retournées 
	  return true;
	else return false;
}

int main(){
	init();
	/*can conv = can();

	usb.send(conv.lecture(0) >> 2);
	_delay_ms(2);*/
	

	MoteurManager engines = MoteurManager();

	//distanceSensor sensor = distanceSensor();
	uint8_t detectedRight;
	uint8_t detectedLeft;

    enum States {
        AVANCER,
        ADJUST_INTER,
		DETECT,
        TURN_LEFT,
        TURN_RIGHT
    };

    // Set the initial state
    States state = AVANCER;
		
	for(;;) {

 		switch (state) {
            case AVANCER:
				engines.avancer(140);

				// 00100
				// 01100
				// 00110
				if (((PINC & 0x1F) == 0x04) || ((PINC & 0x1F) == 0x06) || ((PINC & 0x1F) == 0x0C))  {
					// PORTA = 0x0;
					engines.adjustcenter();
					_delay_ms(10);
				}

				// 00010
				// 00001
				// 00011
				if (((PINC & 0x1F) == 0x01) || ((PINC & 0x1F) == 0x03) || ((PINC & 0x1F) == 0x02)) {
					//PORTA = 0x2;
					engines.adjustToLeft();
					_delay_ms(10);
				}

				// 11000
				// 10000
				// 01000
				if (((PINC & 0x1F) == 0x18) || ((PINC & 0x1F) == 0x10) || ((PINC & 0x1F) == 0x08)) {
				// PORTA = 0x1;
					engines.adjustToRight();
					_delay_ms(10);
				}

				// 11111
				// 00111
				// 11100
				// 01111
				// 11110
				if (((PINC & 0x1F) == 0x1F) || ((PINC & 0x1F) == 0x07) || ((PINC & 0x1F) == 0x1C) ||((PINC & 0x1F) == 0x0F)||((PINC & 0x1F) == 0x1E)) {
					_delay_ms(15);
		
					if(((PINC & 0x1F) == 0x1F) || ((PINC & 0x1F) == 0x07) || ((PINC & 0x1F) == 0x1C) ||((PINC & 0x1F) == 0x0F)||((PINC & 0x1F) == 0x1E)) {
						state = DETECT;
					}
				}
				break;
				
			case DETECT:
				engines.arreter();
				_delay_ms(500);
				
				//incliner légèrement à droite, arrêter puis tester les potaux
				
				engines.avancer(160);
				_delay_ms(200);
				engines.adjustToRight();
				_delay_ms(300);
				engines.arreter();
				_delay_ms(500);
				detectedRight = detecter(50);
				
				//incliner légèrement à gauche, arrêter puis tester les potaux
				engines.adjustToLeft();
				_delay_ms(700);
				engines.arreter();
				_delay_ms(500);
				detectedLeft = detecter(50);
				
				//usb.send(detected);
				if (detectedRight || detectedLeft)		//si un des deux tests est correct
				{		
				 state = ADJUST_INTER;				//tourner
				}
				else
				{
				  engines.avancer(160);
				  _delay_ms(500);
				  state = AVANCER;				//sinon continuer
				}
				break;
	      
				
			case ADJUST_INTER:
				engines.avancer(160);
				_delay_ms(900);
				state = TURN_LEFT;

			case TURN_LEFT:
				
				engines.arreter();
				_delay_ms(500);
				engines.tournerGauche(40);

				while ((PINC & 0x1F) == 0x00) {
					//engines.tournerGauche(1);
					engines.adjustToLeft();
					
				}

				state = AVANCER;

				break;

			case TURN_RIGHT:
				engines.arreter();
				_delay_ms(500);
				engines.tournerDroite(45);

				while ((PINC & 0x1F) == 0x00) {
					//engines.tournerDroite(1);
					engines.adjustToRight();
				}

				state = AVANCER;

				break;


				break;
		}
	}

	return 0;
}

