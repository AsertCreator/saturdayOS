#include "include/memory.h"

void StdCopyMemory(void* dst, void* src, size_t count) {
    for (size_t i = 0; i < count; i++) ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
}
void StdFillMemory(void* dst, uint8_t val, size_t count) {
    for (size_t i = 0; i < count; i++) ((uint8_t*)dst)[i] = val;
}