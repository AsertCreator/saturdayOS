#include "../hals/include/tty.h"

void TtyMgrLog(status st, const char* com, const char* fmt, ...) {
	va_list vl;

	if (DID_FAIL(st))
		tty_color = vga_entry_color(TTY_COLOR_RED, TTY_COLOR_BLACK);
	else
		tty_color = vga_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);

	printf("%s: ", com);

	tty_color = vga_entry_color(TTY_COLOR_LIGHT_GREY, TTY_COLOR_BLACK);
	va_start(vl, fmt);
	vprintf(fmt, vl);
	va_end(vl);

	printf("\n");
}