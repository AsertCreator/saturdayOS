#pragma once
#include "../../include/system.h"

#define TTY_COLOR_BLACK         (uint8_t)0 
#define TTY_COLOR_BLUE          (uint8_t)1 
#define TTY_COLOR_GREEN         (uint8_t)2 
#define TTY_COLOR_CYAN          (uint8_t)3 
#define TTY_COLOR_RED           (uint8_t)4 
#define TTY_COLOR_MAGENTA       (uint8_t)5 
#define TTY_COLOR_BROWN         (uint8_t)6 
#define TTY_COLOR_LIGHT_GREY    (uint8_t)7 
#define TTY_COLOR_DARK_GREY     (uint8_t)8 
#define TTY_COLOR_LIGHT_BLUE    (uint8_t)9 
#define TTY_COLOR_LIGHT_GREEN   (uint8_t)10 
#define TTY_COLOR_LIGHT_CYAN    (uint8_t)11 
#define TTY_COLOR_LIGHT_RED     (uint8_t)12 
#define TTY_COLOR_LIGHT_MAGENTA (uint8_t)13 
#define TTY_COLOR_LIGHT_BROWN   (uint8_t)14 
#define TTY_COLOR_WHITE         (uint8_t)15 

#define TTY_DEFAULT_BACK TTY_COLOR_BLACK
#define TTY_DEFAULT_FORE TTY_COLOR_LIGHT_GREY

#define vga_entry_color(fg, bg) (uint8_t)(fg | bg << 4)
#define vga_entry(uc, color) (uint16_t)uc | (uint16_t)color << 8
#define vga_entry_char(ent) (char)((ent >> 8) << 8)

uint16_t* tty_buffer;
uint8_t tty_sizex;
uint8_t tty_sizey;
uint8_t tty_cursorx;
uint8_t tty_cursory;
uint8_t tty_color;

char TtyMgrGetCharacterAt(uint8_t x, uint8_t y);
void TtyMgrSetCursorPosition(uint8_t x, uint8_t y, char c);
void TtyMgrPutCharacter(char c);
void TtyMgrMoveCursor(uint8_t x, uint8_t y);
void TtyMgrScrollTerminal();
void TtyMgrClearLine(int line);
void TtyMgrClearTerminal();
void TtyMgrInitialize();
void TtyMgrLog(status st, const char* com, const char* fmt, ...);
void printf(const char* fmt, ...);
void vprintf(const char* fmt, va_list list);