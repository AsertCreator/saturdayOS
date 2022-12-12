#include "include/ps2.hpp"

void ps2_init() {

	make_enable_msg("ps2");
}
void ps2_enable() {

}
void ps2_disable() {

}
char ps2_kbd_get() {
	return 'a';
}