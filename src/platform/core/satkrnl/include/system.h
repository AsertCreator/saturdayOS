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

#define NEVER_REFERENCED(x) (void)x
#define SUCCESS (status)0
#define FAILED_GENERAL (status)1
#define FAILED_NOTIMPL (status)2
#define FAILED_NOTALLW (status)3
#define FAILED_NOTAVAL (status)4
#define FAILED_NOTRESP (status)5
#define FAILED_UNREACH (status)6
#define FAILED_NOTFUND (status)7
#define FAILED_OUTOFMM (status)8
#define FAILED_SKIPPED (status)9

#define DID_SUCCESS(x) (x == SUCCESS)
#define DID_FAIL(x)    (x != SUCCESS)

#define SATKRNL_VERSION_MAJOR (int)0
#define SATKRNL_VERSION_MINOR (int)1
#define SATKRNL_VERSION_PATCH (int)0

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
#include "../ex/include/convert.h"
#include "../hals/include/paging.h"
#include "../hals/include/hii.h"
#include "../ex/include/mp.h"
#include "../ex/include/drive.h"
#include "../hals/include/device.h"
#include "../hals/include/syscall.h"
#include "../ex/include/vidtty.h"
#include "../ex/include/schedule.h"
#include "../hals/include/thread.h"
#include "../ex/include/file.h"
#include "../hals/include/uefi.h"

#include "multiboot.h"

extern HeapObject system_heap;
extern char system_cmdline[];