#ifndef KERNEL_H
#define KERNEL_H
#include "common.hpp"

typedef struct {
	uint32_t eip;
	uint16_t fault;
	const char* msg;
	const char* proc;
} panic_data;

typedef struct {
	uint32_t register_eax;
	uint32_t register_ebx;
	uint32_t register_ecx;
	uint32_t register_edx;
	uint32_t register_esi;
	uint32_t register_edi;
	uint32_t register_esp;
	uint32_t register_ebp;
	uint32_t register_efl;
	uint32_t register_eip;
} context_frame;

struct interrupt_frame {
	uint32_t eip;
	uint16_t cs;
	uint32_t eflags;
	uint32_t esp;
	uint16_t ss;
} __attribute__((packed));

typedef struct {
	uint16_t offset_1;        // offset bits 0..15
	uint16_t selector;        // a code segment selector in GDT or LDT
	uint8_t  zero;            // unused, set to 0
	uint8_t  type_attributes; // gate type, dpl, and p fields
	uint16_t offset_2;        // offset bits 16..31
} idt_entry;

extern int kernel_program;

#include "memory.hpp"
#include "gdt.hpp"
#include "ps2.hpp"
#include "tty.hpp"
#include "pit.hpp"
#include "interrupt.hpp"
#include "utility.hpp"

extern "C" {
	void kmain(); 
}

void kernel_restart();
void kernel_shutdown();
void kernel_panic(panic_data* data);

void exczero(struct interrupt_frame* f);

#endif