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
	bool paused;
	void* aux;
	struct tagThreadObject* prev;
	struct tagThreadObject* next;
} ThreadObject;

// TaskObject "<-" SystemObject
typedef struct tagTaskObject {
	ThreadObject* thread;
	ThreadEntry entry;
	volatile bool isdone;
} TaskObject;

extern ThreadObject* current_thread;
extern ThreadObject* first_thread;
extern ThreadObject* last_thread;
extern uint32_t nextip;

void ExInitializeThreading();
void ExRunParralel(ThreadEntry entry, TaskObject* obj);
void ExWaitForTask(TaskObject* obj);
void ExWaitForAllTasksVar(int taskc, ...);
void ExWaitForAllTasks(int taskc, TaskObject** objs);
status ExCreateStandaloneThreadEx(const char* name, RegisterContext ctx, /*out*/ ThreadObject** out);
status ExCreateThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out);
status ExDestroyThread(ThreadObject* obj);
status ExResumeThread(ThreadObject* obj);
status ExPauseThread(ThreadObject* obj);
void HALSwitchThread(RegisterContext* curctx);
status HALCreateStandaloneThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out);
uint32_t HALGetCPUFlags();