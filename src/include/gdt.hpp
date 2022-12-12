#ifndef GDT_H
#define GDT_H
#include "kernel.hpp"

typedef struct {
	uint16_t limit0;
	uint16_t base0;
	uint8_t base1;
	uint8_t access;
	uint8_t limit1 : 4;
	uint8_t flags : 4;
	uint8_t base2;
} gdt_entry;

void gdt_add(uint32_t base, uint32_t limit, uint8_t access, uint8_t flags);
void gdt_init();

#endif // !GDT_H
