#include "../hals/include/tty.h"

void printf(const char* fmt, ...) {
	va_list list;
	va_start(list, fmt);
	vprintf(fmt, list);
	va_end(list);
}
void vprintf(const char* fmt, va_list list) {
	size_t len = StdStringLength(fmt);
	size_t i = 0;
	while (i < len) {
		char c = fmt[i];
		switch (c) {
		case '%': {
			i++;
			c = fmt[i];
			switch (c) {
			case 's': { // sorta posix // print string
				char* data = va_arg(list, char*);
				printf(data);
				break;
			}
			case 'd': { // sorta posix // print number
				char c[12];
				printf(StdIntToString(va_arg(list, int), c, 10));
				break;
			}
			case 'x': { // not posix // print number as hexadecimal
				char c[8];
				StdFillMemory(c, '0', 8);
				printf(StdLongToString((long)va_arg(list, int), c, 16, false));
				break;
			}
			case 'b': { // not posix // print boolean value
				if (va_arg(list, int)) printf("true");
				else printf("false");
				break;
			}
			case '#': { // not posix
				printf("0x");
				break;
			}
			case '%': { // posix
				TtyMgrPutCharacter('%');
				break;
			}
			}
			break;
		}
		default: {
			TtyMgrPutCharacter(c);
			break;
		}
		}
		i++;
	}
	TtyMgrMoveCursor(tty_cursorx, tty_cursory);
}