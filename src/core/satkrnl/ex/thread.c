#include "include/std.h"
#include "include/heap.h"
#include "include/memory.h"
#include "../hals/include/thread.h"
#include "../hals/include/irq.h"

static void TaskEntry() {
	TaskObject* obj = (TaskObject*)current_thread->aux;
	obj->thread = current_thread;
	obj->entry();
	obj->isdone = true;
}
void ExInitializeThreading() {
	HALSetIRQHandler(0, HALSwitchThread);
}
void ExRunParralel(ThreadEntry entry, TaskObject* out) {
	ThreadObject* obj;
	ExCreateThread("Task Thread", TaskEntry, 16 * 1024, &obj);
	out->entry = entry;
	out->isdone = false;
	out->thread = obj;
	obj->aux = out;
	ExResumeThread(obj);
}
void ExWaitForTask(TaskObject* obj) {
	while (!obj->isdone) { }
}
void ExWaitForAllTasksVar(int taskc, ...) {
	va_list vl;
	va_start(vl, taskc);
	TaskObject* obj[taskc];

	for (int i = 0; i < taskc; i++) {
		obj[i] = va_arg(vl, TaskObject*);
	}

	va_end(vl);
	
	ExWaitForAllTasks(taskc, obj);
}
void ExWaitForAllTasks(int taskc, TaskObject** objs) {
	bool done = true;
	do {
		for (int i = 0; i < taskc; i++) {
			done &= objs[i]->isdone;
		}
	} while (!done);
}
status ExCreateStandaloneThreadEx(const char* name, RegisterContext ctx, /*out*/ ThreadObject** out) {
	ThreadObject* obj = (ThreadObject*)HeapAlloc(&system_heap, sizeof(ThreadObject));

	if (!obj) return FAILED_OUTOFMM;

	StdFillMemory(obj, 0, sizeof(ThreadObject));
	StdCopyMemory(obj->name, (void*)name, StdStringLength(name));

	obj->ctx = ctx;
	obj->paused = true;

	if (out != NULL)
		*out = obj;

	return SUCCESS;
}
status ExCreateThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out) {
	ThreadObject* obj;

	status result = HALCreateStandaloneThread(name, entry, stacksize, &obj);

	if (result != SUCCESS) return result;

	if (out != NULL)
		*out = obj;

	if (current_thread == 0) {
		first_thread = obj;
		last_thread = obj;
		current_thread = obj;
		obj->next = obj;
	}
	else {
		last_thread->next = obj;
		obj->next = first_thread;
		last_thread = obj;
	}

	return SUCCESS;
}
status ExDestroyThread(ThreadObject* obj) {
	obj->prev->next = obj->next;
	obj->next->prev = obj->prev;

	HeapFree(&system_heap, obj);
	return SUCCESS;
}
status ExResumeThread(ThreadObject* obj) {
	obj->paused = false;
	return SUCCESS;
}
status ExPauseThread(ThreadObject* obj) {
	obj->paused = true;
	return SUCCESS;
}