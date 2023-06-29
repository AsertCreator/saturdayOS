#pragma once
#include "../../include/system.h"

#define SYSCALL_WRITE      0x00000000
#define SYSCALL_READ       0x00000001
#define SYSCALL_OPEN       0x00000002
#define SYSCALL_UNRELIABLE 0xFFFFFFFF

#define STDOUT -1
#define STDIN -2
#define STDERR -3

void ExSetupSyscalls();
void ExHandleSyscall(RegisterContext* ctx);