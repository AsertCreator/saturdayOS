#pragma once
#include "../../include/system.h"

typedef void (*ThreadEntry)(void);

// ThreadObject "<-" SystemObject
typedef struct tagThreadObject {
	char name[64];
	uint32_t privilege;
	uint32_t priority;
	uint32_t tid;
	uint32_t pid;
	RegisterContext ctx;
	struct tagThreadObject* next;
} ThreadObject;

extern ThreadObject* current_thread;
extern ThreadObject* first_thread;
extern ThreadObject* last_thread;

void ExInitializeThreading();
status ExCreateStandaloneThreadEx(const char* name, RegisterContext ctx, /*out*/ ThreadObject** out);
status ExCreateThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out);
status ExDestroyThread(ThreadObject* obj);
status ExResumeThread(ThreadObject* obj);
status ExPauseThread(ThreadObject* obj);
RegisterContext ExSwitchThread(RegisterContext curctx);