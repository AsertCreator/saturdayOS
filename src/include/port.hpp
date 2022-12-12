#ifndef PORT_H
#define PORT_H
#include "common.hpp"

void outb(uint8_t data, uint16_t port);
uint8_t inb(uint16_t port);

#endif