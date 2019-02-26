#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"


ssize_t _write(int fd, const void *buf, size_t count){
char * letter = (char *)(buf);
for(int i = 0; i < count; i++){
uart_send(*letter);
letter++;
}
return count;
}

int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons
	GPIO->PIN_CNF[17] = 0; //Button A
	GPIO->PIN_CNF[26] = 0; //Button B
	uart_init();

	int sleep = 0;
	while(1){

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		 if(!(GPIO->IN & (1 << 26))){
			 GPIO->OUTSET = (1<<13) | (1<<14) | (1<<15);
			 uart_send('B');
		 }
		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */
		 if(!(GPIO->IN & (1 << 17))){
			 GPIO->OUTCLR = (1<<13) | (1<<14) | (1<<15);
			// iprintf("Norway has %d counties.\n\r", 18);
			uart_send('A');
		 }
		 /*if((GPIO->IN &(1<<13))){
			 GPIO->OUTCLR = (1<<13) | (1<<14) | (1<<15);
		 }else if(UART->RXDRDY || !(GPIO->IN &(1<<13))){
			 GPIO->OUTSET = (1<<13) | (1<<14) | (1<<15);
		 }*/
		 uart_send(uart_read());

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}
