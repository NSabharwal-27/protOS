#include "mmu.h"
#include <stdint.h>

/*-- 4 level page tables --*/
static uint64_t l0_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
static uint64_t l1_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
static uint64_t l2_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
static uint64_t l3_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));

static inline __attribute__((always_inline))
void clear_tables() {
	for (int i = 0; i < PAGE_ENTRIES; i++) {
		l0_page_table[i] = 0;
		l1_page_table[i] = 0;
		l2_page_table[i] = 0;
		l3_page_table[i] = 0;
	}
}

void mmu_init() {

	clear_tables();

	/*
			       --l0_page_table setup-- 
		every entry in l0 covers 512 gigs, setup only the 1st
		entry because not much more than that is needed at this
		time.
	 */
	l0_page_table[0] = ( l1_page_table | PTE_TABLE | PTE_VALID );	

	/*
				--l1_page_table setup--
		every entry in l1 covers a 1 gig entry, here we set aside
		a gig for kernel and another for our nGnRnE devices i.e. PL011
	*/
	l1_page_table[0] = ( l2_page_table | PTE_TABLE | PTE_VALID );
	l1_page_table[1] = ( l2_page_table | PTE_TABLE | PTE_VALID );

	/*
				--l2_page_table setup--
		every entry is now 2MB which is huge, so we go another step
	*/
	l2_page_table[0] = ( l3_page_table | PTE_TABLE | PTE_VALID );
	l2_page_table[1] = ( l3_page_table | PTE_TABLE | PTE_VALID );


	return;
}
