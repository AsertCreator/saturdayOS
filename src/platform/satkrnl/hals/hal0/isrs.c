#include "../include/isrs.h"

char* exception_messages[] = {
    "division by zero",
    "debug",
    "non maskable interrupt",
    "breakpoint",
    "into detected overflow",
    "out of nounds",
    "invalid opcode",
    "no coprocessor",

    "double fault",
    "coprocessor segment overrun",
    "bad tss",
    "segment not present",
    "stack fault",
    "general protection fault",
    "page fault",
    "unknown interrupt",

    "coprocessor fault",
    "alignment check",
    "machine check",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",

    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved",
    "reserved"
};

/* This is a very repetitive function... it's not hard, it's
*  just annoying. As you can see, we set the first 32 entries
*  in the IDT to the first 32 ISRs. We can't use a for loop
*  for this, because there is no way to get the function names
*  that correspond to that given entry. We set the access
*  flags to 0x8E. This means that the entry is present, is
*  running in ring 0 (kernel level), and has the lower 5 bits
*  set to the required '14', which is represented by 'E' in
*  hex. */
void HALInitializeTraps() {
    HALInstallIDTGate(0, (unsigned)isr0, 0x08, 0x8E);
    HALInstallIDTGate(1, (unsigned)isr1, 0x08, 0x8E);
    HALInstallIDTGate(2, (unsigned)isr2, 0x08, 0x8E);
    HALInstallIDTGate(3, (unsigned)isr3, 0x08, 0x8E);
    HALInstallIDTGate(4, (unsigned)isr4, 0x08, 0x8E);
    HALInstallIDTGate(5, (unsigned)isr5, 0x08, 0x8E);
    HALInstallIDTGate(6, (unsigned)isr6, 0x08, 0x8E);
    HALInstallIDTGate(7, (unsigned)isr7, 0x08, 0x8E);

    HALInstallIDTGate(8, (unsigned)isr8, 0x08, 0x8E);
    HALInstallIDTGate(9, (unsigned)isr9, 0x08, 0x8E);
    HALInstallIDTGate(10, (unsigned)isr10, 0x08, 0x8E);
    HALInstallIDTGate(11, (unsigned)isr11, 0x08, 0x8E);
    HALInstallIDTGate(12, (unsigned)isr12, 0x08, 0x8E);
    HALInstallIDTGate(13, (unsigned)isr13, 0x08, 0x8E);
    HALInstallIDTGate(14, (unsigned)isr14, 0x08, 0x8E);
    HALInstallIDTGate(15, (unsigned)isr15, 0x08, 0x8E);

    HALInstallIDTGate(16, (unsigned)isr16, 0x08, 0x8E);
    HALInstallIDTGate(17, (unsigned)isr17, 0x08, 0x8E);
    HALInstallIDTGate(18, (unsigned)isr18, 0x08, 0x8E);
    HALInstallIDTGate(19, (unsigned)isr19, 0x08, 0x8E);
    HALInstallIDTGate(20, (unsigned)isr20, 0x08, 0x8E);
    HALInstallIDTGate(21, (unsigned)isr21, 0x08, 0x8E);
    HALInstallIDTGate(22, (unsigned)isr22, 0x08, 0x8E);
    HALInstallIDTGate(23, (unsigned)isr23, 0x08, 0x8E);

    HALInstallIDTGate(24, (unsigned)isr24, 0x08, 0x8E);
    HALInstallIDTGate(25, (unsigned)isr25, 0x08, 0x8E);
    HALInstallIDTGate(26, (unsigned)isr26, 0x08, 0x8E);
    HALInstallIDTGate(27, (unsigned)isr27, 0x08, 0x8E);
    HALInstallIDTGate(28, (unsigned)isr28, 0x08, 0x8E);
    HALInstallIDTGate(29, (unsigned)isr29, 0x08, 0x8E);
    HALInstallIDTGate(30, (unsigned)isr30, 0x08, 0x8E);
    HALInstallIDTGate(31, (unsigned)isr31, 0x08, 0x8E);
}

void HALHandleFault(RegisterContext* r) {
    if (r->int_no < 32) {
        BspMgrIssuePanic(exception_messages[r->int_no]);
        HALHaltCPU();
    }
}
