#include "twi.h"


void twi_init(){
    GPIO->PIN_CNF[30] = (0<<0) | (6<<8)| (3<<2); //SDA
	GPIO->PIN_CNF[0] = (0<<0) | (6<<8)| (3<<2); //SCL
    TWI0->PSELSCL = 0;
    TWI0->PSELSDA = 30;
    TWI0->FREQUENCY = 0x01980000;
    TWI0->ENABLE = 5;
    TWI0->RXDREADY = 0;
    TWI0->ERROR = 0;
    TWI0->TXDSENT = 0;
}
