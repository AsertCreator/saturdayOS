#pragma once
#include "../../include/system.h"

void StdCopyMemory(void* dst, void* src, size_t count);
void StdFillMemory(void* dst, uint8_t val, size_t count);
uint8_t HALInputFromPort(uint16_t _port);
void HALOutputToPort(uint16_t _port, uint8_t _data);