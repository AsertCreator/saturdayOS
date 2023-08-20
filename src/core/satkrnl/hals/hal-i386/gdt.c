#include "include/gdt.h"

gdt_entry gdt[5];
gdt_ptr gp;

void HALSetGDTEntry(uint32_t num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void HALInitializeGDT()
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(gdt_entry) * 5) - 1;
    gp.base = (uint32_t)&gdt;

    HALSetGDTEntry(0, 0, 0, 0, 0);
    HALSetGDTEntry(1, 0, 0xFFFFFFFF, 0x9E, 0xCF);
    HALSetGDTEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    HALSetGDTEntry(3, 0, 0xFFFFFFFF, 0xFE, 0xCF);
    HALSetGDTEntry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    HALInstallLocalGDT();

    DbgPrintStacktrace();
}
