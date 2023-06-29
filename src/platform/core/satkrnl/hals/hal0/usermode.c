#include "../include/usermode.h"

void ExPrepareUsermode() {

}
void ExRunInUsermode(usermode_func func) {
	asm volatile("mov (4 * 8) | 3, %ax");     // ring 3 data with bottom 2 bits set for ring 3
	asm volatile("mov %ax, %ds");
	asm volatile("mov %ax, %es");
	asm volatile("mov %ax, %fs");
	asm volatile("mov %ax, %gs");              // SS is handled by iret
	asm volatile("mov %esp, %eax");	         
	asm volatile("push (4 * 8) | 3");         // data selector
	asm volatile("push %eax");                // current esp
	asm volatile("pushf");                   // eflags
	asm volatile("push (3 * 8) | 3");         // code selector(ring 3 code with bottom 2 bits set for ring 3)
	asm volatile("push %0" : : "a"(func)); // instruction address to return to
	asm volatile("iret");
}