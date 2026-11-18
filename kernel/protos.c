#include <stdint.h>
#include "uart/uart.h"
#include "arm64/mmu/mmu.h"

void kmain(void) {
	uart_init();
	mmu_init();

	kprintf("Hello World!\n");

	while(1);
}
