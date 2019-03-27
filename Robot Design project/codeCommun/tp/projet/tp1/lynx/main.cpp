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
#include "../../libpout/src/sleep.h"
#include "MoteurManager.h"

using namespace libpout;

Serial usb;

void init()
{
	// Debug led
    DDRA = 0x03;

    // PWM output for engines
    DDRD = 0xF0; // OCR1A, OCR1B

	if (debug) {
		usb = Serial();
	}
}

void ajuste( MoteurManager engines)
{
  if ((PINA & 0xA8) == 0x88)  {
            PORTA = 0x0;
            engines.adjustcenter();
        }

       
        if ((PINA & 0xA8) == 0x28) {
            PORTA = 0x2;
            engines.adjustToRight();
	    _delay_ms(10);
        }

        if ((PINA & 0xA8) == 0xA0) {
            PORTA = 0x1;
	     engines.adjustToLeft();
	    _delay_ms(10);
        }
}

/**
 * The main function. It does the logic.
 */
int main()
{
    init();
     //usb.send((PINA & 0xA8));
    MoteurManager engines = MoteurManager();
    engines.avancer(160);

    

    for(;;) {

         ajuste(engines);
         if (((PINA & 0xA8) == 0x00) || ((PINA & 0xA8) == 0x80) || ((PINA & 0xA8) == 0x08) )
	 {
	  
	   _delay_ms(20);
	   if (((PINA & 0xA8) == 0x00) || ((PINA & 0xA8) == 0x80) || ((PINA & 0xA8) == 0x08) )
	     {
	       //_delay_ms(850);
	       engines.arreter();
	       _delay_ms(500);	       
	      	
	     }
	 }
        
    }

    return 0; 
}