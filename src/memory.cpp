#include "include/kernel.hpp"

uint32_t dma_installedram;
uint32_t dma0_address;

void memset(void* dst, uint8_t val, uint32_t len) {
	for (size_t i = 0; i < len; i++) { 
		((uint8_t*)dst)[i] = val; 
	}
}
void memmove(void* src, void* dst, uint32_t len) {
	for (size_t i = 0; i < len; i++) { 
		((uint8_t*)dst)[i] = ((uint8_t*)src)[i]; 
		((uint8_t*)dst)[i] = 0; 
	}
}
void* memalloc(uint32_t len) {
	void* addr = (void*)dma0_address;
	dma0_address += len;
	return addr;
}
void memfree(void* buffer) {
	UNUSED(buffer);
	// todo: implement
}
void dma_init() {
	dma_installedram = 128 * 1024 * 1024;
	dma0_address = 16 * 1024 * 1024;
	make_enable_msg("dma");
}
