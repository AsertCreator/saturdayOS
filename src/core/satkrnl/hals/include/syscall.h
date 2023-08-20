#pragma once
#include "../../include/system.h"

#define DEFINE_REGISTER(reg) register uint32_t* reg asm(#reg)

#define ID_SkGetOSVersion 100
#define ID_SkGetErrorMessage 101
#define ID_SkListDir 102
#define ID_SkCreateDir 103
#define ID_SkCreateFile 104
#define ID_SkDeleteDir 105
#define ID_SkDeleteFile 106
#define ID_SkOpenFile 107
#define ID_SkCloseFile 108
#define ID_SkWriteFile 109
#define ID_SkReadFile 110
#define ID_SkSeekFilePosition 111
#define ID_SkSeekMaxFilePosition 112
#define ID_SkWriteConsole 113
#define ID_SkReadConsole 114
#define ID_SkAllocMemory 115
#define ID_SkFreeMemory 116
#define ID_SkGetArgv 117
#define ID_SkGetArgc 118
#define ID_SkGetPid 119
#define ID_SkTerminate 120
#define ID_SkCreateObject 121
#define ID_SkDestroyObject 122
#define ID_SkDefineObject 123
#define ID_SkUndefineObject 124
#define ID_SkLockMutex 125
#define ID_SkUnlockMutex 126
#define ID_SkPushMessage 127
#define ID_SkPopMessage 128
#define ID_SkCheckRemainingMessages 129
#define ID_SkExecuteProcess 130
#define ID_SkGetLastProcessError 131

int SkGetOSVersion();
char* SkGetErrorMessage(status err);
status SkListDir(char* path, /*out*/ char*** els);
status SkCreateDir(char* path);
status SkCreateFile(char* path);
status SkDeleteDir(char* path);
status SkDeleteFile(char* path);
status SkOpenFile(char* path, char mode, /*out*/ fd_t* fd);
status SkCloseFile(fd_t fd);
status SkWriteFile(fd_t fd, char* ch, int ix, int sz);
status SkReadFile(fd_t fd, /*out*/ char* buf, int ix, int sz);
status SkSeekFilePosition(fd_t fd, /*out*/ int* out);
status SkSeekMaxFilePosition(fd_t fd, /*out*/ int* out);
status SkWriteConsole(char* str, int am);
status SkReadConsole(/*out*/ char** buf, /*out*/ int* c);
status SkAllocMemory(uint32_t sz, /*out*/ void** out);
status SkFreeMemory(void* mem);
status SkGetArgv(/*out*/ char*** out);
status SkGetArgc(/*out*/ int* out);
status SkGetPid(/*out*/ pid_t* out);
status SkTerminate(pid_t pid, /*out*/ int* out);
status SkCreateObject(uuid_t* objid, void** out);
status SkDestroyObject(void** in);
status SkDefineObject(uuid_t* objid, void** in, size_t sz);
status SkUndefineObject(uuid_t* objid);
status SkLockMutex(int mutexid);
status SkUnlockMutex(int mutexid);
status SkPushMessage(pid_t pid, int msg, int arg0, int arg1);
status SkPopMessage(int* msg, int* arg0, int* arg1);
int SkCheckRemainingMessages();
status SkExecuteProcess(const char* path, const char* args, const char* env);
status SkGetLastProcessError();

void ExSetupSyscalls();
void ExHandleSyscall(RegisterContext* ctx);