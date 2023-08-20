#pragma once
#include "../../../include/system.h"

// IDTEntry "<-" SystemObject
typedef struct
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed)) IDTEntry;

// IDTPointer "<-" SystemObject
typedef struct
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) IDTPointer;

extern IDTEntry idt[];
extern IDTPointer idtp;

void HALInstallLocalIDT();
void HALInstallIDTGate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);
void HALInitializeIDT();