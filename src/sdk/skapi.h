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

typedef uint32_t status_t;
typedef uint32_t pid_t;
typedef uint32_t fd_t;

#define DEFINE_REGISTER(reg) register uint32_t* reg asm(#reg)
#define DO_SYSCALL asm volatile("int $0x80")

static inline int SkGetOSVersion() {
	DEFINE_REGISTER(eax);
	eax = (uint32_t*)100000;
	DO_SYSCALL;
	return (int)eax;
}
static inline int SkGetAPIVersion() {
	return 1;
}
static inline char* SkGetErrorMessage(status_t err) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100001;
	ebx = (uint32_t*)err;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (char*)eax;
}
static inline status_t SkListDir(char* path, /*out*/ char*** els) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100002;
	ebx = (uint32_t*)path;
	DO_SYSCALL;
	*els = (char**)ebx;
	return (status_t)eax;
}
static inline status_t SkCreateDir(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100003;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkCreateFile(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100004;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkDeleteDir(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100005;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkDeleteFile(char* path) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100006;
	ebx = (uint32_t*)path;
	NEVER_REFERENCED(ebx);
	DO_SYSCALL;
	return (status_t)eax;
}
static inline status_t SkOpenFile(char* path, char mode, /*out*/ fd_t* fd) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)100007;
	ebx = (uint32_t*)path;
	ecx = (uint32_t*)(uint32_t)mode;
	NEVER_REFERENCED(ecx);
	DO_SYSCALL;
	*fd = (fd_t)ebx;
	return (status_t)eax;
}
static inline status_t SkCloseFile(fd_t fd) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100008;
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
	eax = (uint32_t*)100009;
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
	eax = (uint32_t*)100010;
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
	eax = (uint32_t*)100011;
	ebx = (uint32_t*)fd;
	DO_SYSCALL;
	*out = (int)ebx;
	return (status_t)eax;
}
static inline status_t SkSeekMaxFilePosition(fd_t fd, /*out*/ int* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100012;
	ebx = (uint32_t*)fd;
	DO_SYSCALL;
	*out = (int)ebx;
	return (status_t)eax;
}
static inline status_t SkWriteConsole(char* str, int am) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	DEFINE_REGISTER(ecx);
	eax = (uint32_t*)100013;
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
	eax = (uint32_t*)100014;
	ebx = (uint32_t*)buf;
	DO_SYSCALL;
	*buf = (char*)ebx;
	*c = (int)ecx;
	return (status_t)eax;
}
static inline status_t SkAllocMemory(uint32_t sz, /*out*/ void** out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100015;
	ebx = (uint32_t*)sz;
	DO_SYSCALL;
	*out = (void*)ebx;
	return (status_t)eax;
}
static inline status_t SkFreeMemory(void* mem) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100016;
	ebx = (uint32_t*)mem;
	DO_SYSCALL;
	NEVER_REFERENCED(ebx);
	return (status_t)eax;
}
static inline status_t SkGetArgv(/*out*/ char*** out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100017;
	DO_SYSCALL;
	*out = (char**)ebx;
	return (status_t)eax;
}
static inline status_t SkGetArgc(/*out*/ int* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100018;
	DO_SYSCALL;
	*out = (int)ebx;
	return (status_t)eax;
}
static inline status_t SkGetPid(/*out*/ pid_t* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100019;
	DO_SYSCALL;
	*out = (pid_t)ebx;
	return (status_t)eax;
}
static inline status_t SkTerminate(pid_t pid, /*out*/ int* out) {
	DEFINE_REGISTER(eax);
	DEFINE_REGISTER(ebx);
	eax = (uint32_t*)100020;
	ebx = (uint32_t*)pid;
	DO_SYSCALL;
	*out = (int)ebx;
	return (status_t)eax;
}