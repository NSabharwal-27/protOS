#include "mmu.h"
#include <stdint.h>

static uint64_t l0_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
static uint64_t l1_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
static uint64_t l2_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));
static uint64_t l3_page_table[PAGE_ENTRIES] __attribute__((aligned(PAGE_SIZE)));


static inline void clear_tables() {
	for (int i = 0; i < PAGE_ENTRIES; i++) {
		l0_page_table[i] = 0;
		l1_page_table[i] = 0;
		l2_page_table[i] = 0;
		l3_page_table[i] = 0;
	}
}

void mmu_init() {
	clear_tables();

	return;
}
