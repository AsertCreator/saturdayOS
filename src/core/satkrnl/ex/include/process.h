#pragma once
#include "../../include/system.h"

typedef uint32_t pid_t;

// ProcessObject "<-" SystemObject
typedef struct tagProcessObject {
	const char* path;
	const char* domain;
	const char* user;
	pid_t pid;
	int thread_count;
	struct tagThreadObject** thread_list;
	int memory_used;
	int memory_alloccount;
	void** memory_allocs;
	int env_varcount;
	char** env_vars;
	const char* args;
	int child_count;
	struct tagProcessObject* next_global;
	struct tagProcessObject* prev_global;
	struct tagProcessObject* next_sibling;
	struct tagProcessObject* prev_sibling;
	struct tagProcessObject* parent;
	struct tagProcessObject* first_child;
	ElfHeader32 elf_header;
	ElfProgramHeader32* elf_phs;
	ElfSectionHeader32* elf_shs;
} ProcessObject;

extern ProcessObject* current_process;
extern ProcessObject* kernel_process;
extern ProcessObject* last_process;
extern pid_t next_pid;
extern int process_count;

void ExInitializeProcessing();
ProcessObject* ExCreateDeadProcess(const char* domain, const char* user, ProcessObject* root);
ProcessObject* ExFindProcess(pid_t pid);
ProcessObject* ExCreateProcess(const char* path, const char* arg, const char* domain, const char* user, ProcessObject* root);
ProcessObject* ExGetProcessChild(ProcessObject* po, int n);
void ExTerminateProcess(pid_t pid);