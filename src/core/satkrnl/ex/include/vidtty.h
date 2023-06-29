#pragma once
#include "../../include/system.h"

typedef struct {
	uint16_t r;
	uint16_t g;
	uint16_t b;
} color16;

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} color8;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t szx;
	uint16_t szy;
} rect;

extern uint8_t* vt_fb;
extern uint16_t vt_sizex;
extern uint16_t vt_sizey;

#define SET_PIXEL(x, y, col) \
	vt_fb[(vt_sizex * y + x) * 3] = col.r; \
	vt_fb[(vt_sizex * y + x) * 3 + 1] = col.g; \
	vt_fb[(vt_sizex * y + x) * 3 + 2] = col.b;

void VidTtySetMode();
void VidTtySetFramebuffer(uint8_t* fb, uint16_t sizex, uint16_t sizey);
void VidTtyDrawString(const char* str, uint16_t x, uint16_t y, color8 col);
void VidTtyFillRectangle(rect rect, color8 col);
void VidTtyClear(color8 col);
color8 VidTtyConvertColor16(color16 col);
color16 VidTtyConvertColor8(color8 col);
static inline color8 MakeRGB(uint8_t r, uint8_t g, uint8_t b) {
	color8 col = { 0 };
	col.r = r;
	col.g = g;
	col.b = b;
	return col;
}
static inline color16 MakeRGB16(uint16_t r, uint16_t g, uint16_t b) {
	color16 col = { 0 };
	col.r = r;
	col.g = g;
	col.b = b;
	return col;
}