#pragma once
#include "../../include/system.h"

typedef struct
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed)) gdt_entry;

typedef struct
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) gdt_ptr;

extern gdt_entry gdt[];
extern gdt_ptr gp;

void HALInstallLocalGDT();
void HALSetGDTEntry(uint32_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
void HALInitializeGDT();