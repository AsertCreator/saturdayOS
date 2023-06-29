#pragma once
#include <stdint.h>

uint8_t HALInputFromPort(uint16_t _port);
void HALOutputToPort(uint16_t _port, uint8_t _data);