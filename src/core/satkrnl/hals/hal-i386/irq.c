#include "../include/irq.h"
#include "include/idt.h"

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
void HALSetIRQHandler(int irq, void (*handler)(RegisterContext*)) {
    irq_routines[irq] = handler;
}

void HALUnsetIRQHandler(int irq) {
    irq_routines[irq] = 0;
}

void HALInitializePIC(void) {
    HALOutputToPort(0x20, 0x11);
    HALOutputToPort(0xA0, 0x11);
    HALOutputToPort(0x21, 0x20);
    HALOutputToPort(0xA1, 0x28);
    HALOutputToPort(0x21, 0x04);
    HALOutputToPort(0xA1, 0x02);
    HALOutputToPort(0x21, 0x01);
    HALOutputToPort(0xA1, 0x01);
    HALOutputToPort(0x21, 0x0);
    HALOutputToPort(0xA1, 0x0);
}

void HALInitializeInterrupts() {
    HALInitializePIC();

    HALInstallIDTGate(32, (unsigned)irq0, 0x08, 0x8E);
    HALInstallIDTGate(33, (unsigned)irq1, 0x08, 0x8E);
    HALInstallIDTGate(34, (unsigned)irq2, 0x08, 0x8E);
    HALInstallIDTGate(35, (unsigned)irq3, 0x08, 0x8E);
    HALInstallIDTGate(36, (unsigned)irq4, 0x08, 0x8E);
    HALInstallIDTGate(37, (unsigned)irq5, 0x08, 0x8E);
    HALInstallIDTGate(38, (unsigned)irq6, 0x08, 0x8E);
    HALInstallIDTGate(39, (unsigned)irq7, 0x08, 0x8E);

    HALInstallIDTGate(40, (unsigned)irq8, 0x08, 0x8E);
    HALInstallIDTGate(41, (unsigned)irq9, 0x08, 0x8E);
    HALInstallIDTGate(42, (unsigned)irq10, 0x08, 0x8E);
    HALInstallIDTGate(43, (unsigned)irq11, 0x08, 0x8E);
    HALInstallIDTGate(44, (unsigned)irq12, 0x08, 0x8E);
    HALInstallIDTGate(45, (unsigned)irq13, 0x08, 0x8E);
    HALInstallIDTGate(46, (unsigned)irq14, 0x08, 0x8E);
    HALInstallIDTGate(47, (unsigned)irq15, 0x08, 0x8E);
}

void HALCommonIRQHandler(RegisterContext *r) {
    void (*handler)(RegisterContext *r);

    handler = irq_routines[r->int_no - 32];

    if (handler) handler(r);

    if (r->int_no >= 40) HALOutputToPort(0xA0, 0x20); // PIC Slave EOI
    HALOutputToPort(0x20, 0x20);                      // PIC Master EOI
}

void HALEnableInterrupts() {
    asm volatile("sti");
}
void HALDisableInterrupts() {
    asm volatile("cli");
}