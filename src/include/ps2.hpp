#ifndef PS2_H
#define PS2_H
#include "kernel.hpp"

void ps2_init();
void ps2_enable();
void ps2_disable();
char ps2_kbd_get();

#endif // !PS2_H
