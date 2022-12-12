#ifndef MEMORY_H
#define MEMORY_H
#include "kernel.hpp"

extern uint32_t dma_installedram;

struct dma_mapentry {
	uint32_t size;
	uint32_t addr;
	bool free;
	bool freeable;
	dma_mapentry* next;
};

void memset(void* dst, uint8_t val, uint32_t len);
void memmove(void* src, void* dst, uint32_t len);
void* memalloc(uint32_t len);
void memfree(void* buffer);
void dma_init();

#endif