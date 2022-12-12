#include "include/kernel.hpp"

static gdt_entry entries[5];
static int gdtindex;
static uint32_t gdtbase;
static uint16_t gdtsize;
static uint64_t gdtr;

void gdt_add(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	uint8_t* target = (uint8_t*)(&entries);
	target[gdtindex * 8 + 0] = limit & 0xFF;
	target[gdtindex * 8 + 1] = (limit >> 8) & 0xFF;
	target[gdtindex * 8 + 6] = (limit >> 16) & 0x0F;

	target[gdtindex * 8 + 2] = base & 0xFF;
	target[gdtindex * 8 + 3] = (base >> 8) & 0xFF;
	target[gdtindex * 8 + 4] = (base >> 16) & 0xFF;
	target[gdtindex * 8 + 7] = (base >> 24) & 0xFF;

	target[gdtindex * 8 + 5] = access;

	target[gdtindex * 8 + 6] |= (flags << 4);
	gdtindex++;
}

void gdt_init() {
	gdt_add(0, 0, 0, 0); // null descriptor
	gdt_add(0x00, 0xFFFFF, 0x9A, 0x0C); // kmode code
	gdt_add(0x00, 0xFFFFF, 0x92, 0x0C); // kmode data
	gdt_add(0x00, 0xFFFFF, 0xFA, 0x0C); // umode code
	gdt_add(0x00, 0xFFFFF, 0xF2, 0x0C); // umode data
	gdtbase = (uint32_t)&entries;
	gdtsize = sizeof(entries);
	gdtr |= gdtsize;
	gdtr |= (gdtbase >> 16);
	asm volatile ("lgdt (%%eax)" : : "a"(&gdtr));
	make_enable_msg("gdt");
}