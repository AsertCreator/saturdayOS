#include "include/kernel.hpp"
#include "include/interrupt.hpp"

int kernel_program;

__attribute__ ((interrupt))
void inttest(struct interrupt_frame* f) {
	UNUSED(f);
	printf("int test might be working lol xd lmao hehe~\n");
}
__attribute__ ((interrupt))
void pittest(struct interrupt_frame* f) {
	UNUSED(f);
	printf("pit test might be working too! lol xd lmao hehe~\n");
}

extern "C" {
	void kmain() {
		register int* multiboot asm("ebx");
		void* addr = (void*)multiboot;

		tty_init();
		printf("loading satkrnl...\n");

		// platform initialization
		make_log_block("platform initialization");
		{
			make_enable_msg("tty");
			gdt_init();
			idt_init();
			dma_init();
			ps2_init();
			idt_setinthandler(0x00, &exczero);
			idt_setinthandler(0x80, &inttest);
			idt_setirqhandler(0x00, &pittest);
			pit_init(10);
		}

		// user shell initialization
		make_log_block("user shell initialization");
		{
			printf("welcome to saturdayOS!\n\n");

			// statistics, p e r h a p s
			printf("gdt entry size: ");
			printi(sizeof(gdt_entry));
			printf("\n");
			printf("idt entry size: ");
			printi(sizeof(idt_entry));
			printf("\n");
			printf("multiboot struct address: ");
			printf("0x");
			printh((uint32_t)addr);
			printf("\n\n");

			// actual initialization
			kernel_program = 1;

			printf("printf test 1!%s\n");
			printf("printf test 2!%d\n");
		}

		// user interaction
		make_log_block("user interaction");
		{
			bool running = true;
			switch (kernel_program) {
				// tshell ripoff/spinoff
				case 0: {
					printf("well yes! its an tshell spinoff!\nenter commands and get responses!\neasy as it can be!\n");
					while (running) {
						printf("> ");
						//tty_read(c, &len);
						while (1) {}
						printf("\n");
					}
					break;
				}
				// test
				case 1: {
					break;
				}
				// unknown shell
				default: {
					make_error_msg("shell is not selected! system will halt now");
					while (1) {}
					break;
				}
			}
		}
	}
}

void kernel_restart() {

}
void kernel_shutdown() {
}

void kernel_panic(panic_data* data) {
	UNUSED(data);
	tty_color = vga_entry_color(TTY_COLOR_RED, TTY_COLOR_BLACK);
	printf("something died");
}

void exczero(struct interrupt_frame* f) {
	panic_data* panic = { 0 };
	panic->eip = f->eip;
	panic->fault = 0;
	panic->msg = "division by zero";
	panic->proc = "kernel mode";
	kernel_panic(panic);
}