#include "../include/thread.h"

ThreadObject* current_thread;
ThreadObject* first_thread;
ThreadObject* last_thread;

status HALCreateStandaloneThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out) {
	ThreadObject* obj = (ThreadObject*)HeapAlloc(&system_heap, sizeof(ThreadObject));

	if (!obj) return FAILED_OUTOFMM;

	StdFillMemory(obj, 0, sizeof(ThreadObject));
	StdCopyMemory(obj->name, (void*)name, StdStringLength(name));

	if (obj->privilege == 0) {
		obj->ctx.cs = 1 * 8;
		obj->ctx.ds = 2 * 8;
		obj->ctx.es = 2 * 8;
		obj->ctx.fs = 2 * 8;
		obj->ctx.gs = 2 * 8;
		obj->ctx.ss = 2 * 8;
	}
	if (obj->privilege == 1) {
		obj->ctx.cs = 3 * 8;
		obj->ctx.ds = 4 * 8;
		obj->ctx.es = 4 * 8;
		obj->ctx.fs = 4 * 8;
		obj->ctx.gs = 4 * 8;
		obj->ctx.ss = 4 * 8;
	}

	obj->ctx.eip = (uint32_t)entry;
	obj->ctx.esp = (uint32_t)HeapAlloc(&system_heap, stacksize) + stacksize;

	if (!obj->ctx.esp) return FAILED_OUTOFMM;

	*out = obj;

	return SUCCESS;
}