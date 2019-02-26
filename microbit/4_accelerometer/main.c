#include <stdint.h>
#include <stdio.h>
#include "gpio.h"



int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	
	return 0;
}
