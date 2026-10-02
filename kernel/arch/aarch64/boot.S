/*
 * Create a custom section with Allocate (a)
 * and eXecute (x) perms.
 * align it to 2^12=4096 bytes. 
 */
.section TT_L0, "ax"
.align 12

/*
 * fill a 4096 byte block full of 0's
 * each entry is 8 bytes, so there is a total of:
 * 4096/8 = 512 entries.
 */
.global tt_l0_base
tt_l0_base:
	.fill   4096, 8, 0

/*
 * potential settings for our MMU
 * IPSIZE:0b101 [34:32]
 * TG0:0b00 [15:14]
 * TG1:0b00 [31:30]
 * T0SZ: 10d48 [21:16]
 * T1SZ: 10d48 [5:0]
 * I think this is enough to get us going for now
 */

.section .text.boot
.global _start
_start:
	/* Sort out the Exception Level first. */
	mrs     x0, CurrentEL
	lsr     x0, x0, #2
	cmp     x0, #1
	beq     .EL1_INITIALIZE


.EL1_INITIALIZE:
	/*
	 * Ram defined in the linker script starts at
	 * 0x0000_0000_4000_0000. So we use TTBR0_EL1.
	 */
	ldr     x0, =tt_l0_base
	msr     TTBR0_EL1, x0

	/*
	 * zero out the system register, and apply the settings
	 * into TCR_EL1
	 */
	msr     TCR_EL1, xzr
	mov     x1, xzr
	mov     x1, #(0b101 << 32)
//	orr     x1, x1, #(0b00 << 14) Caused a complaint but seems unnecessary?
//	orr     x1, x1, #(0b00 << 30) like it's zero anyways, God I wish QEMU would dump sys regs.
	orr     x1, x1, #(48 << 16)
	orr     x1, x1, #(48 << 0)
	msr     TCR_EL1, x1

	/* Now, setup the stack. */
	ldr     x9, =_stack_top
	mov     sp, x9
	ldr     x1, =__bss_start
	ldr     x2, =__bss_end
	b       .bss_clear

/* 
 * We are going to do 8-byte stores, so we can get that
 * 8-byte alignment, from linker.
 */
.bss_clear:
	cmp     x1, x2
	bge     .CALL_KMAIN
	str     xzr, [x1], #8
	b       .bss_clear

.CALL_KMAIN:
	/* Now that's done, go to kernel */
	bl      kmain
	b       .
