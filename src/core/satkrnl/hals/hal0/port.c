#include "../include/port.h"

uint8_t HALInputFromPort(uint16_t _port) {
    uint8_t rv;
    asm volatile("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
uint16_t HALInputFromPortWord(uint16_t _port) {
    uint16_t rv = 0;
    asm volatile("inw %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
uint32_t HALInputFromPortDWord(uint16_t _port) {
    uint32_t rv = 0;
    asm volatile("inl %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}
void HALOutputToPort(uint16_t _port, uint8_t _data) {
    asm volatile("outb %1, %0" : : "dN" (_port), "a" (_data));
}
void HALOutputToPortWord(uint16_t _port, uint16_t _data) {
    asm volatile("outw %1, %0" : : "dN" (_port), "a" (_data));
}
void HALOutputToPortDWord(uint16_t _port, uint32_t _data) {
    asm volatile("outl %1, %0" : : "dN" (_port), "a" (_data));
}