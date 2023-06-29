#include "../hals/include/thread.h"

void ExInitializeThreading() {
	
}
status ExCreateStandaloneThreadEx(const char* name, RegisterContext ctx, /*out*/ ThreadObject** out) {
	ThreadObject* obj = (ThreadObject*)HeapAlloc(&system_heap, sizeof(ThreadObject));

	if (!obj) return FAILED_OUTOFMM;

	StdFillMemory(obj, 0, sizeof(ThreadObject));
	StdCopyMemory(obj->name, (void*)name, StdStringLength(name));

	obj->ctx = ctx;

	*out = obj;

	return SUCCESS;
}
status ExCreateThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out) {
	ThreadObject* obj;

	status result = HALCreateStandaloneThread(name, entry, stacksize, &obj);

	if (result != SUCCESS) return result;

	*out = obj;

	last_thread->next = obj;
	obj->next = first_thread;
	last_thread = obj;

	return SUCCESS;
}
status ExDestroyThread(ThreadObject* obj) {
	NEVER_REFERENCED(obj);
	return SUCCESS;
}
status ExResumeThread(ThreadObject* obj) {
	NEVER_REFERENCED(obj);
	return SUCCESS;
}
status ExPauseThread(ThreadObject* obj) {
	NEVER_REFERENCED(obj);
	return SUCCESS;
}
RegisterContext ExSwitchThread(RegisterContext curctx) {
	current_thread->ctx = curctx;
	current_thread = current_thread->next;
	return current_thread->ctx;
}