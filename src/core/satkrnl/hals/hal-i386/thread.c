#include "../include/thread.h"
#include "../include/timer.h"
#include "../include/tty.h"
#include "../../ex/include/std.h"
#include "../../ex/include/heap.h"
#include "../../ex/include/memory.h"

ThreadObject* current_thread = 0;
ThreadObject* first_thread = 0;
ThreadObject* last_thread = 0;

static bool first_switch = true;
static int timer = 0;

status HALCreateStandaloneThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out) {
	ThreadObject* obj = (ThreadObject*)HeapAlloc(&system_heap, sizeof(ThreadObject));

	if (!obj) return FAILED_OUTOFMM;

	StdFillMemory(obj, 0, sizeof(ThreadObject));
	StdCopyMemory(obj->name, (void*)name, StdStringLength(name));

	obj->ctx.eflags = HALGetCPUFlags();

	obj->ctx.cs = 1 * 8;
	obj->ctx.ds = 2 * 8;
	obj->ctx.es = 2 * 8;
	obj->ctx.fs = 2 * 8;
	obj->ctx.gs = 2 * 8;
	obj->ctx.ss = 2 * 8;

	DEBUG_HEX((uint32_t)entry);

	obj->ctx.eip = (uint32_t)entry;
	obj->ctx.esp = (uint32_t)HeapAlloc(&system_heap, stacksize) + stacksize;
	obj->ctx.ebp = obj->ctx.esp;
	obj->ctx.int_no = 0x20;

	if (!obj->ctx.esp) return FAILED_OUTOFMM;

	obj->paused = false;

	if (out != NULL)
		*out = obj;

	return SUCCESS;
}
void HALSwitchThread(RegisterContext* curctx) {
	HALTimerIRQHandler(curctx);

	if (timer++ % 4 == 0) {
		if (!first_switch) {
			current_thread->ctx.eax = curctx->eax;
			current_thread->ctx.ebx = curctx->ebx;
			current_thread->ctx.ecx = curctx->ecx;
			current_thread->ctx.edx = curctx->edx;
			current_thread->ctx.esi = curctx->esi;
			current_thread->ctx.edi = curctx->edi;
			current_thread->ctx.esp = curctx->esp;
			current_thread->ctx.ebp = curctx->ebp;
			current_thread->ctx.eip = curctx->eip;
			current_thread->ctx.eflags = curctx->eflags;
		}

		first_switch = false;

	retry:
		current_thread = current_thread->next;
		if (current_thread->paused)
			goto retry;

		curctx->eax = current_thread->ctx.eax;
		curctx->ebx = current_thread->ctx.ebx;
		curctx->ecx = current_thread->ctx.ecx;
		curctx->edx = current_thread->ctx.edx;
		curctx->esi = current_thread->ctx.esi;
		curctx->edi = current_thread->ctx.edi;
		curctx->esp = current_thread->ctx.esp;
		curctx->ebp = current_thread->ctx.ebp;
		curctx->eip = current_thread->ctx.eip;
		curctx->eflags = current_thread->ctx.eflags;
	}
}