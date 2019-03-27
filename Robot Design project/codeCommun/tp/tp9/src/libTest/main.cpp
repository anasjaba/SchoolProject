/**
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include "../libpout/src/led.h"
#include "../libpout/src/serial.h"
#include "../libpout/src/sleep.h"
#include "../libpout/src/pwm.h"
#include "../libpout/src/memoire_24.h"
#include "../libpout/src/pwmSon.h"
#include "../Piezoelectrique.h"

using namespace libpout;

Serial usb;

void init()
{
	// Debug led
    DDRA = 0x03;

    // PWM output for engines
    DDRD = 0xF0; // OCR1A, OCR1B

    // PWM output for the sound
    DDRB = 0x0C; // OCR0A

	usb = Serial();
}

/**
 * We assume that the Serial class does work.
 * In fact, it does work.
 */
int main()
{
	init();
    PORTD = 0x2;
    
    // test delay
    //PORTA = 0x1;
    //msleep(2000);
    //PORTA = 0x2;
    //msleep(2000);
    //PORTA = 0x0;

    // test led class
    //led led1 = led(Ports::A, 0, 1);
    //led1.lightOnRed();
    //msleep(2000);
    //led1.lightOnGreen();
    //msleep(2000);
    //led1.lightOff();

    // test pwm class
    //PWM engine = PWM(OCR::A1, 0);
    //engine.start();
    //msleep(2000);
    //engine.adjust(64);
    //msleep(2000);
    //engine.adjust(128);
    //msleep(2000);
    //engine.adjust(200);
    //msleep(2000);
    //engine.adjust(255);
    //msleep(2000);
    //engine.stop();

    // test son

    //pwmSon son = pwmSon();
    //son.start();
    //son.adjust(142);
    //msleep(2000);
    //son.adjust();
    //msleep(2000);
    //son.adjust();
    //msleep(2000);
    //son.adjust();
    //son.stop();
    //Piezoelectrique piezo = Piezoelectrique();
    //piezo.setFrequency(45);
    //piezo.start();


    for(;;){}

    return 0; 
}