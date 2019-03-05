#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ubit.h"

#include "bluetooth.h"

int main(){
	ubit_uart_init();

	uint32_t err_code = 0;
	uint32_t err_code2 = 0;

	err_code = bluetooth_init();
	err_code2 = bluetooth_gap_advertise_start();
	ubit_uart_print("BLE Enable error code: %d\n\r", err_code);
	ubit_uart_print("Buetooth error test: %d\n\r", err_code2);


	return 0;
}
