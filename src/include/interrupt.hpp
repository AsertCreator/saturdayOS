#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "kernel.hpp"
#define IDT_SIZE 256

void idt_init();
void idt_setinthandler(uint16_t i, void (*handler)(struct interrupt_frame*));
void idt_setirqhandler(uint16_t i, void (*handler)(struct interrupt_frame*));

#endif // !INTERRUPT_H
