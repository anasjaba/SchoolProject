/**
 *
 * @author Louis Racicot & Samuel Rondeau
 * @created: 2014-10-16
 * @modified: Look at the SVN
 */

#define F_CPU 8000000UL
#define debug true
#define program_size 106
#include <avr/io.h>
#include <string.h>
#include "src/libpout/src/led.h"
#include "src/libpout/src/serial.h"
#include "src/libpout/src/sleep.h"
#include "src/libpout/src/memoire_24.h"
#include "ledManager.h"
#include "Piezoelectrique.h"
#include "MoteurManager.h"

using namespace libpout;

Serial usb;


class Instruction
{
public:
    Instruction(){}
    Instruction(uint8_t opcode_, uint8_t operand_);
	uint8_t opcode;
	uint8_t operand;
};

Instruction::Instruction(uint8_t opcode_, uint8_t operand_) : opcode(opcode_), operand(operand_) {}

void init()
{
	// Debug led
    DDRA = 0x03;

    // PWM output for engines
    DDRD = 0xF0; // OCR1A, OCR1B

    // PWM output for the sound
    DDRB = 0x0C; // OCR0A

	if (debug) {
		usb = Serial();
	}
}

/**
 * The main function. It does the logic.
 */
int main()
{
	init();

    bool begin = false;
    bool stop = false;

    // Instanciate all classes
    ledManager leds = ledManager();
    MoteurManager engines = MoteurManager();
    Piezoelectrique son = Piezoelectrique();
    Memoire24CXXX mem = Memoire24CXXX();

    Instruction instr;
    uint16_t base_pointer = 0;
    uint8_t boucle_iter = 0;

    for (uint16_t i = 0; i < program_size && !stop; i=i+2 ) {

        // Read the program data
        uint8_t program_data[2];
        mem.lecture(i, program_data, 2);

        instr = Instruction(program_data[0], program_data[1]);

        // If we received a dbt inscruction
        if (begin) {

            switch (instr.opcode) {
                case 0x2: // att (25ms * operand)
                    msleep(25*instr.operand);
                    break;

                case 0x44: // dal (led number)
                    leds.lightOn(instr.operand);
                    break;

                case 0x45: // det (led number)
                    leds.lightOff(instr.operand);
                    break;

                case 0x48: // sgo (fréquence)
                    son.setFrequency(instr.operand);
                    son.start();
                    break;

                case 0x09: // sar
                    son.stop();
                    break;

                case 0x60: // mar
                case 0x61: // mar
                    engines.arreter();
                    break;

                case 0x62: // mav (speed)
                    engines.avancer(instr.operand);
                    break;

                case 0x63: // mre (speed)
                    engines.reculer(instr.operand);
                    break;

                case 0x64: // trd
                    engines.tournerDroite();
                    break;

                case 0x65: // trg
                    engines.tournerGauche();
                    break;

                case 0xC0: // dbc (iterations)
                    base_pointer = i;
                    boucle_iter = instr.operand;
                    break;

                case 0xC1: // fbc (iterations)
                    if (boucle_iter > 0) {
                        boucle_iter--;
                        i = base_pointer;
                    }
                    break;

                case 0xff: // fin
                    //son.stop();
                    //engines.arreter();
                    stop = true;
            }


        } else if (instr.opcode == 0x01) {
            begin = true;
        }
        //usb.send(instr.opcode);
        //usb.send(instr.operand);
    } 

    for(;;){}

    return 0; 
}