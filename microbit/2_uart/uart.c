
#include <stdint.h>
#include "uart.h"
#include "gpio.h"




void uart_init(){
  GPIO->PIN_CNF[25] = 0; //RXD input
	GPIO->PIN_CNF[24] = 1; //TXD Output
  UART->PSELTXD = 24;
  UART->PSELRXD = 25;
  UART->BAUDRATE = 0x00275000;
  UART->PSELRTS = 0xFFFFFFFF;
  UART->PSELCTS = 0xFFFFFFFF;
  UART->ENABLE = 4;
  UART->STARTRX = 1;

}

void uart_send(char letter){
	UART->STARTTX = 1;
	UART->TXD = (char)letter;

 while (UART->TXDRDY!=1)
 {
	 // Wait for TXD data to be sent
 }

 UART->TXDRDY=0;
 UART->STARTTX = 0;
 UART->STOPTX = 1;

}

char uart_read(){
	if (UART->RXDRDY != 1)
	  {
			return '\0';
	  }

	UART->RXDRDY = 0;
	if((GPIO->IN &(1<<13))){
		GPIO->OUTCLR = (1<<13) | (1<<14) | (1<<15);
	} else if(!(GPIO->IN &(1<<13))){
		GPIO->OUTSET = (1<<13) | (1<<14) | (1<<15);
	}
	return (char)UART->RXD;
}

void uart_send_str(char ** str){
	UART->STARTTX = 1;
	char * letter_ptr = *str;
	while(*letter_ptr != '\0'){
			UART->TXD = *letter_ptr;
			while(!UART->TXDRDY);
			UART->TXDRDY = 0;
			letter_ptr++;
		}
}
