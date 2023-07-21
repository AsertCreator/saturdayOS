#pragma once
#include "../../include/system.h"

void StdCopyMemory(void* dst, void* src, size_t count);
void StdFillMemory(void* dst, uint8_t val, size_t count);
void StdFillMemoryW(void* dst, uint16_t val, size_t count);