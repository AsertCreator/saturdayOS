#include "include/pit.hpp"
#include "include/port.hpp"

void pit_init(uint16_t freq) {
	int divisor = 1193180 / freq;
    outb(0x36, 0x43);
    outb(divisor & 0xFF, 0x40);
    outb(divisor >> 8, 0x40);
    make_enable_msg("pit");
}
void pit_waitfor(uint16_t ms) {
    UNUSED(ms);
}