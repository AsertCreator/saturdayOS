#pragma once
#include "../../include/system.h"

extern void* irq_routines[];

void HALSetIRQHandler(int irq, void (*handler)(RegisterContext*));
void HALUnsetIRQHandler(int irq);
void HALInitializeInterrupts();
void HALEnableInterrupts();
void HALDisableInterrupts();

#define ENTER_CRITICAL_ZONE HALDisableInterrupts()
#define LEAVE_CRITICAL_ZONE HALEnableInterrupts()

void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();