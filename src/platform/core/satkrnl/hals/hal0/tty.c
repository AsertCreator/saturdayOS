#include "../include/tty.h"

uint16_t* tty_buffer;
uint8_t tty_sizex;
uint8_t tty_sizey;
uint8_t tty_cursorx;
uint8_t tty_cursory;
uint8_t tty_color;

void TtyMgrInitialize() {
	tty_sizex = 80;
	tty_sizey = 25;
	tty_cursorx = 0;
	tty_cursory = 0;
	tty_color = vga_entry_color(TTY_DEFAULT_FORE, TTY_DEFAULT_BACK);
	tty_buffer = (uint16_t*)0xB8000;
	TtyMgrClearTerminal();
}
void TtyMgrSetCursorPosition(uint8_t x, uint8_t y, char c) {
	const size_t index = y * tty_sizex + x;
	tty_buffer[index] = vga_entry(c, tty_color);
}
char TtyMgrGetCharacterAt(uint8_t x, uint8_t y) {
	const size_t index = y * tty_sizex + x;
	return vga_entry_char(tty_buffer[index]);
}
void TtyMgrPutCharacter(char c) {
	if (c == '\n') {
		tty_cursorx = 0;
		TtyMgrScrollTerminal();
		return;
	}
	TtyMgrSetCursorPosition(tty_cursorx, tty_cursory, c);
	if (++tty_cursorx == tty_sizex) {
		tty_cursorx = 0;
		if (++tty_cursory == tty_sizey)
			TtyMgrScrollTerminal();
	}
}
void TtyMgrMoveCursor(uint8_t x, uint8_t y) {
	uint16_t pos = y * tty_sizex + x;
	HALOutputToPort(0x3D4, 0x0F);
	HALOutputToPort(0x3D5, (uint8_t)(pos & 0xFF));
	HALOutputToPort(0x3D4, 0x0E);
	HALOutputToPort(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
void TtyMgrScrollTerminal() {
	if (tty_cursory < tty_sizey) {
		tty_cursory++;
	}
	else {
		TtyMgrClearTerminal();
	}
}
void TtyMgrClearLine(int line) {
	size_t index = (line - 1) * tty_sizex;
	for (size_t x = 0; x < tty_sizex; ++x) {
		tty_buffer[index + x] = vga_entry(' ', tty_color);
	}
}
void TtyMgrClearTerminal() {
	for (size_t y = 0; y < tty_sizey; y++) {
		for (size_t x = 0; x < tty_sizex; x++) {
			size_t index = y * tty_sizex + x;
			tty_buffer[index] = vga_entry(' ', tty_color);
		}
	}
	tty_cursorx = 0;
	tty_cursory = 0;
}
void TtyMgrLog(status st, const char* com, const char* fmt, ...) {
	va_list vl;

	if (DID_FAIL(st))
		tty_color = vga_entry_color(TTY_COLOR_RED, TTY_COLOR_BLACK);
	else
		tty_color = vga_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);

	printf("[%s] ", com);

	tty_color = vga_entry_color(TTY_COLOR_LIGHT_GREY, TTY_COLOR_BLACK);
	va_start(vl, fmt);
	vprintf(fmt, vl);
	va_end(vl);

	printf("\n");
}