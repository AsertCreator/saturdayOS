#pragma once
#include <stdint.h>

uint8_t HALInputFromPort(uint16_t _port);
uint16_t HALInputFromPortWord(uint16_t _port);
uint32_t HALInputFromPortDWord(uint16_t _port);
void HALOutputToPort(uint16_t _port, uint8_t _data);
void HALOutputToPortWord(uint16_t _port, uint16_t _data);
void HALOutputToPortDWord(uint16_t _port, uint32_t _data);