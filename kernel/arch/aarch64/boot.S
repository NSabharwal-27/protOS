.section .text.boot
.global _start
_start:
	/* Sort out the Exception Level first. */
	mrs     x0, CurrentEL
	lsr     x0, x0, #2
	cmp     x0, #1
	beq     .el1_setup

.el1_setup:
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
	bge     .call_kmain
	str     xzr, [x1], #8
	b       .bss_clear

.call_kmain:
	/* Now that's done, go to kernel */
	bl      kmain
	b       .
