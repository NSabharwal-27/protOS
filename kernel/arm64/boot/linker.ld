ENTRY(_start)
SECTIONS {
	/* RAM starts at 0x4000_0000 */
	. = 0x40000000;

	/*
	 * This is news to me, on AARCH64 the registers are
	 * 64 bits, but the instructions themselves are 32 bits
	 * Which really threw me for a loop but wtv.
	 */
	. = ALIGN(4);
	.text : { 
		*.(.text.boot)
		*.(.text)
	}

	. = ALIGN(8);
	.data : { *(.data) }

	. = ALIGN(8);
	.rodata : { *(.rodata) }

	/* 
	 * We can do 16-byte or 8-byte alignment,
	 * it depends on the way that we clear the bss section
	 * in the assembly boot code. We will opt for 8.
	 */
	. = ALIGN(8);
	.bss : {
		__bss_start = .;
		*(.bss)
		. = ALIGN(8);
		__bss_end = .;
	}

	/* Align the stack, 16-byte alignment */
	. = ALIGN(16);
	_stack_end = .;
	/* 
	 * Reserve 16KB for the stack, we know
	 * it's already aligned.
	 */
	. += 0x4000;
	_stack_top = .;
}
