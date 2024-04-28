#pragma once

// this is saturdayOS native api. wow.

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

// some basic api
#define STDOUT -1
#define STDERR -2
#define STDIN -3
#define INVALID -4

#define MODE_READ 'r'
#define MODE_WRITE 'w'
#define MODE_APPEND 'a'

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
#define FAILED_BADREQT 0x0000000A
#define FAILED_BADRESP 0x0000000B

#define PERMISSION_CONTROL_UUID { 0x3AF3DD3F, 0xC206, 0x4880, 0xAC04, 0x8C8064CC, 0x1A29 }

#define DID_SUCCESS(x) (x == SUCCESS)
#define DID_FAIL(x)    (x != SUCCESS)

typedef uint32_t status_t;
typedef uint32_t pid_t;
typedef uint32_t fd_t;

typedef struct {
	uint32_t a;
	uint16_t b;
	uint16_t c;
	uint16_t d;
	uint32_t e;
	uint16_t f;
} uuid_t;

#define DEFINE_REGISTER(reg) register uint32_t* reg asm(#reg)
#define DO_SYSCALL asm volatile("int $0x80")

static inline int SkGetOSVersion() {
	DEFINE_REGISTER(eax);
	eax = (uint32_t*)100;
	DO_SYSCALL;
	return (int)eax;
}
static inline int SkGetAPIVersion() {
	return 1;
}
static inline char* SkGetErrorMessage(status_t err) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)101;
	ebx = (uint32_t*)err;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (char*)eax;
}
static inline status_t SkListDir(char* path, /*out*/ char*** els) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)102;
	ebx = (uint32_t*)path;
	ecx = (uint32_t*)els;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkCreateDir(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)103;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkCreateFile(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)104;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkDeleteDir(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)105;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkDeleteFile(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)106;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkOpenFile(char* path, char mode, /*out*/ fd_t* fd) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	DEFINE_REGISTER(edx);
	eax = (uint32_t*)107;
	ebx = (uint32_t*)path;
	ecx = (uint32_t*)(uint32_t)mode;
	edx = (uint32_t*)fd;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	NEVER_REFERENCED(edx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkCloseFile(fd_t fd) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)108;
	ebx = (uint32_t*)fd;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkWriteFile(fd_t fd, char* ch, int ix, int sz) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	DEFINE_REGISTER(edx);
	DEFINE_REGISTER(esi);
	eax = (uint32_t*)109;
	ebx = (uint32_t*)fd;
	ecx = (uint32_t*)ch;
	edx = (uint32_t*)ix;
	esi = (uint32_t*)sz;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	NEVER_REFERENCED(edx);
	NEVER_REFERENCED(esi);
	return (status_t)eax;
}
static inline status_t SkReadFile(fd_t fd, /*out*/ char* buf, int ix, int sz) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	DEFINE_REGISTER(edx);
	DEFINE_REGISTER(esi);
	eax = (uint32_t*)110;
	ebx = (uint32_t*)fd;
	ecx = (uint32_t*)buf;
	edx = (uint32_t*)ix;
	esi = (uint32_t*)sz;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	NEVER_REFERENCED(edx);
	NEVER_REFERENCED(esi);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkSeekFilePosition(fd_t fd, /*out*/ int* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)111;
	ebx = (uint32_t*)fd;
	ecx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkSeekMaxFilePosition(fd_t fd, /*out*/ int* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)112;
	ebx = (uint32_t*)fd;
	ecx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkWriteConsole(char* str, int am) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)113;
	ebx = (uint32_t*)str;
	ecx = (uint32_t*)am;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkReadConsole(/*out*/ char** buf, /*out*/ int* c) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)114;
	ebx = (uint32_t*)buf;
	ecx = (uint32_t*)c;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkAllocMemory(uint32_t sz, /*out*/ void** out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)115;
	ebx = (uint32_t*)sz;
	ecx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkFreeMemory(void* mem) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)116;
	ebx = (uint32_t*)mem;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkGetArgv(/*out*/ char*** out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)117;
	ebx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkGetArgc(/*out*/ int* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)118;
	ebx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkGetPid(/*out*/ pid_t* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)119;
	ebx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkTerminate(pid_t pid, /*out*/ int* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)120;
	ebx = (uint32_t*)pid;
	ecx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkCreateObject(uuid_t* objid, void** out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)121;
	ebx = (uint32_t*)objid;
	ecx = (uint32_t*)out;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	return (status_t)eax;
}
static inline status_t SkDestroyObject(void** in) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)122;
	ebx = (uint32_t*)in;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkDefineObject(uuid_t* objid, void** in, size_t sz) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	DEFINE_REGISTER(edx);
	eax = (uint32_t*)123;
	ebx = (uint32_t*)objid;
	ecx = (uint32_t*)in;
	edx = (uint32_t*)sz;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	NEVER_REFERENCED(edx);
	return (status_t)eax;
}
static inline status_t SkUndefineObject(uuid_t* objid) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)124;
	ebx = (uint32_t*)objid;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkLockMutex(int mutexid) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)125;
	ebx = (uint32_t*)mutexid;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkUnlockMutex(int mutexid) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)126;
	ebx = (uint32_t*)mutexid;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkPushMessage(pid_t pid, int msg, int arg0, int arg1) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	DEFINE_REGISTER(edx);
	DEFINE_REGISTER(esi);
	eax = (uint32_t*)127;
	ebx = (uint32_t*)pid;
	ecx = (uint32_t*)msg;
	edx = (uint32_t*)arg0;
	esi = (uint32_t*)arg1;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	NEVER_REFERENCED(edx);
	NEVER_REFERENCED(esi);
	return (status_t)eax;
}
static inline status_t SkPopMessage(int* msg, int* arg0, int* arg1) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	DEFINE_REGISTER(edx);
	eax = (uint32_t*)128;
	ebx = (uint32_t*)msg;
	ecx = (uint32_t*)arg0;
	edx = (uint32_t*)arg1;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	NEVER_REFERENCED(edx);
	return (status_t)eax;
}
static inline int SkCheckRemainingMessages() {
	DEFINE_REGISTER(eax);
	eax = (uint32_t*)129;
	DO_SYSCALL;
	return (int)eax;
}
static inline status_t SkExecuteProcess(const char* path, const char* args, const char* env) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	DEFINE_REGISTER(edx);
	eax = (uint32_t*)130;
	ebx = (uint32_t*)path;
	ecx = (uint32_t*)args;
	edx = (uint32_t*)env;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	NEVER_REFERENCED(ecx);
	NEVER_REFERENCED(edx);
	return (status_t)eax;
}
static inline status_t SkGetLastProcessError() {
	DEFINE_REGISTER(eax);
	eax = (uint32_t*)131;
	DO_SYSCALL;
	return (status_t)eax;
}