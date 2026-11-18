#ifndef UART_H
#define UART_H

#include <stdint.h>

/*
 * ARM Manual Reference: 
 *https://support.arm.com/documentation/100964/1103-00/Peripheral-and-Interface-Components/Peripheral-components/PL011-Uart-component
 * The table looks something like this:
 *  | NAME     | OFFSET | ACCESS |  DESCRIPTION           |
 *  | UARTDR   | 0x00   | R/W    |  Data reg              |
 *  | UARTRSR  | 0x04   | R      |  Receive reg           |
 *  | UARTECR  | 0x04   | W      |  Error Clear           |
 *  | UARTFR   | 0x18   | R      |  Flag Reg              |
 *  | UARTILPR | 0x20   | R/W    |  Low power ctr         |
 *  | UARTIBRD | 0x24   | R/W    |  Int baud rate divisor |
 *  | UARTFBRD | 0x28   | R/W    |  fra baud rate divisor |
 *  | UARTLCR_H| 0x2C   | R/W    |  Line ctrl, high byte  |
 *  | UARTCR   | 0x30   | R/W    |  Control Register      |
 *  | UARTFLS  | 0x34   | R/W    |  Interrupt FIFO lvl sel|
 *  | UARTMSC  | 0x38   | R/W    |  Interrupt mask set/clr|
 *  | UARTRIS  | 0x3C   | R      |  Raw interrupt status  |
 *  | UARTMIS  | 0x40   | R      |  Masked interrupt reg  |
 *  | UARTICR  | 0x44   | W      |  Interrupt clear reg   |
 *  | UARTDMACR| 0x48   | R/W    |  DMA control reg       |
 *
 * So we will use this table as our source of truth to setup the UART stuff below.
 */

/* QEMU documentation puts the PL011 at Address 0x0900_0000 */
#define UART_BASE_ADDR  0x09000000

/* Register offsets, from the table above. */
#define UARTDR          0x000
#define UARTFR          0x018
#define UARTIBRD        0x024
#define UARTFBRD        0x028
#define UARTLCR_H       0x02C
#define UARTCR          0x030

/* Control register bits */
#define UARTCR_EN       (1 << 0)     /* enable */
#define UARTCR_DA       (0 << 0)     /* disable */
#define UARTCR_TXE      (1 << 8)
#define UARTCR_RXE      (1 << 9)

/* line configuration */
#define UARTLCR_H_FEN   (1 << 4)     /* enable FIFO */
#define UARTLCR_H_WLEN  (3 << 5)     /* Word length 8 bits */

#define UARTFR_TXFF     (1 << 5)

#define UART_ACCESS_REG(offset) \
		(*(volatile uint32_t *)(UART_BASE_ADDR + (offset)))

void uart_init();
void uart_putc(const char c);
void uart_puts(const char *str);
void kprintf(const char *str);

#endif /* UART_H */
