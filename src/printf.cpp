#include "include/kernel.hpp"

void printf(const char* fmt, ...) {
	size_t len = strlen(fmt);
	size_t i = 0;
	while (i < len) {
		char c = fmt[i];
		switch (c) {
			case '%': {
				i++;
				c = fmt[i];
				switch (c) {
					case 's': {
						tty_puts("le teste lol lmao hehe shi");
						break; 
					}
					case 'd': {
						printi(7);
						break; 
					}
				}
				break; 
			}
			default: {
				tty_putc(c);
				break; 
			}
		}
		i++;
	}
	tty_movecursor(tty_cursorx, tty_cursory);
}
void printi(int num) {
	char c[12];
	printf(itoa(num, c, 10));
}
void printh(int num) {
	char c[12];
	printf(itoa(num, c, 16));
}