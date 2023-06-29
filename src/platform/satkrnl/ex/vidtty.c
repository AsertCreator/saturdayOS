#include "include/vidtty.h"

uint8_t* vt_fb;
uint16_t vt_sizex;
uint16_t vt_sizey;

color8 VidTtyConvertColor16(color16 col) {
	color8 c = { 0, 0, 0 };
	c.r = (uint8_t)col.r;
	c.g = (uint8_t)col.g;
	c.b = (uint8_t)col.b;
	return c;
}
color16 VidTtyConvertColor8(color8 col) {
	color16 c = { 0, 0, 0 };
	c.r = (uint16_t)col.r;
	c.g = (uint16_t)col.g;
	c.b = (uint16_t)col.b;
	return c;
}
void VidTtySetMode() {
	VidTtyClear(MakeRGB(255, 0, 255));
}
void VidTtySetFramebuffer(uint8_t* fb, uint16_t sizex, uint16_t sizey) {
	vt_fb = fb;
	vt_sizex = sizex;
	vt_sizey = sizey;
}
void VidTtyDrawString(const char* str, uint16_t x, uint16_t y, color8 col) {
	NEVER_REFERENCED(str);
	NEVER_REFERENCED(x);
	NEVER_REFERENCED(y);
	NEVER_REFERENCED(col);
}
void VidTtyFillRectangle(rect rect, color8 col) {
	NEVER_REFERENCED(rect);
	NEVER_REFERENCED(col);
}
void VidTtyClear(color8 col) {
	for (uint16_t y = 0; y < vt_sizey; y++) {
		for (uint16_t x = 0; x < vt_sizex; x++) {
			SET_PIXEL(x, y, col);
		}
	}
}