#include "include/utility.hpp"

uint32_t findoccurr(const char* str, char f) {
    size_t c = 0;
    size_t i = 0;
    while (str[i]) {
        if (str[i] == f) c++;
    }
    return c;
}
size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
void reverse(char *str, int len)
{ 
    int i, temp;
    for (i = 0; i < len / 2; i++)
    { 
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
char* ltoa(long num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
    if (isNegative)
        str[i++] = '-';
    str[i] = '\0';
    reverse(str, i);
    return str;
}
char* itoa(int num, char* str, int base)
{
    return ltoa((long)num, str, base);
}
void make_log_block(const char* name) {
    tty_color = vga_entry_color(TTY_COLOR_GREEN, TTY_COLOR_BLACK);
    printf("\n!! current stage: \"");
    printf(name);
    printf("\" !!\n");
    tty_color = vga_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);
}
void make_enable_msg(const char* msg) {
    tty_color = vga_entry_color(TTY_COLOR_LIGHT_BLUE, TTY_COLOR_BLACK);
    printf("!!! initialized component: \"");
    printf(msg);
    printf("\" !!!\n");
    tty_color = vga_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);
}
void make_error_msg(const char* msg) {
    tty_color = vga_entry_color(TTY_COLOR_RED, TTY_COLOR_BLACK);
    printf("!!!! an error occurred: \"");
    printf(msg);
    printf("\" !!!!\n");
    tty_color = vga_entry_color(TTY_COLOR_WHITE, TTY_COLOR_BLACK);
}