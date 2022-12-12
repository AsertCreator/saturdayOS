#ifndef PIT_H
#define PIT_H
#include "kernel.hpp"

#define PIT_PORT_CH0 (uint16_t)0x40
#define PIT_PORT_CH1 (uint16_t)0x41
#define PIT_PORT_CH2 (uint16_t)0x42
#define PIT_PORT_CMD (uint16_t)0x43

extern void (*pit_currenthandler)(void*);

void pit_init(uint16_t freq);
void pit_waitfor(uint16_t ms);

#endif // !PIT_H
