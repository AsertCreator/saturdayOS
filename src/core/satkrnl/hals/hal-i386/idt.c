#include "include/idt.h"

IDTEntry idt[256];
IDTPointer idtp;

void HALInstallIDTGate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void HALInitializeIDT()
{
    idtp.limit = sizeof(IDTEntry) * 256 - 1;
    idtp.base = (uint32_t)&idt;

    StdFillMemory(&idt, 0, sizeof(IDTEntry) * 256);

    HALInstallLocalIDT();
}
