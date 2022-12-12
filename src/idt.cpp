#include "include/interrupt.hpp"

static idt_entry entries[IDT_SIZE];
static void (*handlers[IDT_SIZE])(struct interrupt_frame*);

void idt_init() {
	for (size_t i = 0; i < IDT_SIZE; i++)
	{
		uint32_t addr = (uint32_t)(&(handlers[i]));
		entries[i].offset_1 = (addr >> 16) << 16;
		entries[i].offset_2 = addr << 16;
		entries[i].selector = 1;
		entries[i].type_attributes = 0x8E;
	}
	asm volatile ("lidt (%%eax)" : : "a"(entries));
	make_enable_msg("idt");
}
void idt_setinthandler(uint16_t i, void (*handler)(struct interrupt_frame*)) {
	handlers[i] = handler;
	asm volatile ("lidt (%%eax)" : : "a"(entries));
}
void idt_setirqhandler(uint16_t i, void (*handler)(struct interrupt_frame*)) {
	handlers[i + 0x20] = handler;
	asm volatile ("lidt (%%eax)" : : "a"(entries));
}