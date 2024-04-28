#include "include/process.h"
#include "include/memory.h"
#include "include/heap.h"
#include "../hals/include/thread.h"

ProcessObject* current_process;
ProcessObject* kernel_process;
ProcessObject* last_process;
pid_t next_pid;
int process_count;
static char** main_envs;

void ExInitializeProcessing() {
	kernel_process = (ProcessObject*)HeapAlloc(&system_heap, sizeof(ProcessObject));
	last_process = kernel_process;

	StdFillMemory(kernel_process, 0, sizeof(ProcessObject));

	main_envs = HeapAlloc(&system_heap, 3 * sizeof(char*));

	main_envs[0] = "PATH=/system/bin;";
	main_envs[1] = "PROCNUM=1";
	main_envs[2] = "PROCARCH=x86";

	kernel_process->path = "/system/core/satkrnl";
	kernel_process->args = system_cmdline;
	kernel_process->domain = "satkrnl authority"; // hey that's windows nt reference!
	kernel_process->user = "system";
	kernel_process->env_vars = main_envs;
	kernel_process->env_varcount = 3;
	kernel_process->next_global = kernel_process;
	kernel_process->prev_global = kernel_process;
	kernel_process->next_sibling = kernel_process;
	kernel_process->parent = 0;

	process_count = 1;
}
ProcessObject* ExCreateDeadProcess(const char* domain, const char* user, ProcessObject* root) {
	ProcessObject* process = (ProcessObject*)HeapAlloc(&system_heap, sizeof(ProcessObject));

	StdFillMemory(process, 0, sizeof(ProcessObject));

	char** cloneenvs = (char**)HeapAlloc(&system_heap, root->env_varcount * sizeof(char*));
	StdCopyMemory(cloneenvs, root->env_vars, root->env_varcount * sizeof(char*));

	process->path = "<dead process>";
	process->args = "";
	process->domain = domain; // hey that's windows nt reference!
	process->user = user;
	process->env_vars = cloneenvs;
	process->env_varcount = root->env_varcount;
	process->next_global = kernel_process;
	process->prev_global = last_process;
	process->next_sibling = root->first_child;
	process->prev_sibling = ExGetProcessChild(root, root->child_count - 1);
	process->parent = root;

	last_process->next_global = process;
	kernel_process->prev_global = process;

	last_process = process;

	root->child_count++;

	return process;
}
ProcessObject* ExFindProcess(pid_t pid) {
	ProcessObject* po = kernel_process;

	for (int i = 0; i < process_count; i++) {
		if (po->pid == pid) return po;
		po = po->next_global;
	}

	return 0;
}
ProcessObject* ExCreateProcess(const char* path, const char* arg, const char* domain, const char* user, ProcessObject* root) {
	NEVER_REFERENCED(path);
	NEVER_REFERENCED(arg);
	NEVER_REFERENCED(domain);
	NEVER_REFERENCED(user);
	NEVER_REFERENCED(root);

	// todo: do that map and execute sht
	return 0;
}
ProcessObject* ExGetProcessChild(ProcessObject* po, int n) {
	ProcessObject* obj = po->first_child;
	for (int i = 0; i < po->child_count; i++) {
		if (i == n) return obj;
		obj = obj->next_sibling;
	}
	return 0;
}
void ExTerminateProcess(pid_t pid) {
	ProcessObject* obj = ExFindProcess(pid);
	if (obj == 0) return;

	// kill its entire family
	
	for (int i = 0; i < obj->child_count; i++) 
		ExTerminateProcess(ExGetProcessChild(obj, i)->pid);

	// thats a bad joke

	obj->parent->child_count--;
	obj->next_sibling->prev_sibling = obj->prev_sibling;
	obj->prev_sibling->next_sibling = obj->next_sibling;
	obj->next_global->prev_global = obj->prev_global;
	obj->prev_global->next_global = obj->next_global;

	process_count--;

	// clean up its blood

	for (int i = 0; i < obj->thread_count; i++)
		ExDestroyThread(obj->thread_list[i]);

	HeapFree(&system_heap, obj->thread_list);
	HeapFree(&system_heap, obj->elf_phs);
	HeapFree(&system_heap, obj->elf_shs);
	HeapFree(&system_heap, obj->env_vars);

	for (int i = 0; i < obj->memory_alloccount; i++)
		HeapFree(&system_heap, obj->memory_allocs);

	HeapFree(&system_heap, obj->memory_allocs);

	// bad joke again. that's it.

	HeapFree(&system_heap, obj);

	if (current_process != 0 && current_process->pid == pid) // if we're we do that
		for (;;);
}