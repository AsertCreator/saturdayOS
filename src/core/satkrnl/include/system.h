#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

// RegisterContext "<-" SystemObject
typedef struct {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} RegisterContext;

// SystemObject
typedef struct { } SystemObject;

// status <- unsigned int
typedef uint32_t status;

#define TO_STRING(x) #x
#define TO_STRINGX(x) TO_STRING(x)

#define ENTER_CRITICAL_ZONE HALDisableInterrupts()
#define LEAVE_CRITICAL_ZONE HALEnableInterrupts()

#define NEVER_REFERENCED(x) (void)x
#define SUCCESS 0x00000000
#define FAILED_GENERAL 0x00000001
#define FAILED_NOTIMPL 0x00000002
#define FAILED_NOTALLW 0x00000003
#define FAILED_NOTAVAL 0x00000004
#define FAILED_NOTRESP 0x00000005
#define FAILED_UNREACH 0x00000006
#define FAILED_NOTFUND 0x00000007
#define FAILED_OUTOFMM 0x00000008
#define FAILED_SKIPPED 0x00000009

#define DID_SUCCESS(x) (x == SUCCESS)
#define DID_FAIL(x)    (x != SUCCESS)

#define SATKRNL_VERSION_MAJOR 0
#define SATKRNL_VERSION_MINOR 2
#define SATKRNL_VERSION_PATCH 0

#define DEBUG printf("!!! debug, file: %s, line: %s !!!\n", __FILE__, TO_STRINGX(__LINE__))
#define DEBUG_HEX(x) printf("!!! debug, file: %s, line: %s, number: %x !!!\n", __FILE__, TO_STRINGX(__LINE__), x)
#define NORETURN __attribute__ ((noreturn))

#include "../ex/include/elf.h"
#include "../hals/include/power.h"
#include "../hals/include/usermode.h"
#include "../hals/include/port.h"
#include "../ex/include/heap.h"
#include "../ex/include/llist.h"
#include "../ex/include/memory.h"
#include "../hals/include/timer.h"
#include "../ex/include/panic.h"
#include "../hals/include/tty.h"
#include "../hals/include/gdt.h"
#include "../hals/include/idt.h"
#include "../hals/include/irq.h"
#include "../hals/include/isrs.h"
#include "../hals/include/pci.h"
#include "../ex/include/convert.h"
#include "../hals/include/paging.h"
#include "../hals/include/hii.h"
#include "../ex/include/mp.h"
#include "../ex/include/drive.h"
#include "../hals/include/device.h"
#include "../hals/include/syscall.h"
#include "../ex/include/vidtty.h"
#include "../hals/include/thread.h"
#include "../ex/include/file.h"
#include "../hals/include/uefi.h"
#include "../hals/include/serial.h"
#include "../hals/include/debug.h"

#include "multiboot.h"

extern HeapObject system_heap;
extern char system_cmdline[];