#include <stdint.h>
#include "uart/uart.h"

void kmain(void) {
	uart_init();
	kprintf("Hello World!\n");

	while(1);
}
