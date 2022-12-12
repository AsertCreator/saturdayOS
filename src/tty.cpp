#include "include/tty.hpp"
#include "include/port.hpp"

uint16_t* tty_buffer;
uint8_t tty_sizex;
uint8_t tty_sizey;
uint8_t tty_cursorx;
uint8_t tty_cursory;
uint8_t tty_color;

void tty_setat(uint8_t x, uint8_t y, char c) {
	const size_t index = y * tty_sizex + x;
	tty_buffer[index] = vga_entry(c, tty_color);
}
char tty_getat(uint8_t x, uint8_t y) {
	const size_t index = y * tty_sizex + x;
	return vga_entry_char(tty_buffer[index]);
}
void tty_putc(char c) {
	if (c == '\n') {
		tty_cursorx = 0;
		tty_scroll();
		return;
	}
	tty_setat(tty_cursorx, tty_cursory, c);
	if (++tty_cursorx == tty_sizex) {
		tty_cursorx = 0;
		if (++tty_cursory == tty_sizey)
			tty_scroll();
	}
}
void tty_puts(const char* s) {
	size_t i = 0;
	size_t z = strlen(s);
	while (s[i] != 0x03 && i < z) {
		tty_putc(s[i]);
		i++;
	}
	tty_movecursor(tty_cursorx, tty_cursory);
}
void tty_movecursor(uint8_t x, uint8_t y)
{
	uint16_t pos = y * tty_sizex + x;
	outb(0x0F, 0x3D4);
	outb((uint8_t)(pos & 0xFF), 0x3D5);
	outb(0x0E, 0x3D4);
	outb((uint8_t)((pos >> 8) & 0xFF), 0x3D5);
}
void tty_scroll() {
	if (tty_cursory < tty_sizey) {
		tty_cursory++;
	}
	else {
		tty_cls();
		tty_cursorx = 0;
		tty_cursory = 0;
	}
}
void tty_cls() {
	for (size_t y = 0; y < tty_sizey; y++) {
		for (size_t x = 0; x < tty_sizex; x++) {
			const size_t index = y * tty_sizex + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}
}
void tty_init() {
	tty_sizex = 80;
	tty_sizey = 25;
	tty_cursorx = 0;
	tty_cursory = 0;
	tty_color = vga_entry_color(TTY_COLOR_LIGHT_GREY, TTY_COLOR_BLACK);
	tty_buffer = (uint16_t*)0xB8000;
	tty_cls();
}
void tty_read(char* buffer, size_t* len) {
	bool keep = true;
	int i = 0;
	while(keep) {
		char c = ps2_kbd_get();
		if (c != -1) {
			buffer[i] = c;
			tty_putc(c);
			i++;
		}
	}
	tty_puts("\n");
	*len = i;
}