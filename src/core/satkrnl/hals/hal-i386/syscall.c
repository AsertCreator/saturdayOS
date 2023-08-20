#include "../../include/system.h"
#include "include/idt.h"

bool log_syscalls = false;

void isr128();

void ExSetupSyscalls() {
    HALInstallIDTGate(0x80, (unsigned)isr128, 0x08, 0xEE);
}
void ExHandleSyscall(RegisterContext* ctx) {
    uint32_t id = ctx->eax;
    uint32_t arg0 = ctx->ebx;
    uint32_t arg1 = ctx->ecx;
    uint32_t arg2 = ctx->edx;
    uint32_t arg3 = ctx->esi;

    status result;

    if (log_syscalls)
        printf("syscall: id=%x, arg0=%x, arg1=%x, arg2=%x, arg3=%x\n", id, arg0, arg1, arg2, arg3);

    switch (id) {
    case ID_SkGetOSVersion:
        result = (status)SkGetOSVersion();
        break;
    case ID_SkGetErrorMessage:
        result = (status)SkGetErrorMessage((status)arg0);
        break;
    case ID_SkListDir:
        result = (status)SkListDir((char*)arg0, (char***)arg1);
        break;
    case ID_SkCreateDir:
        result = (status)SkCreateDir((char*)arg0);
        break;
    case ID_SkCreateFile:
        result = (status)SkCreateFile((char*)arg0);
        break;
    case ID_SkDeleteDir:
        result = (status)SkDeleteDir((char*)arg0);
        break;
    case ID_SkDeleteFile:
        result = (status)SkDeleteFile((char*)arg0);
        break;
    case ID_SkOpenFile:
        result = (status)SkOpenFile((char*)arg0, (char)arg1, (fd_t*)arg2);
        break;
    case ID_SkCloseFile:
        result = (status)SkCloseFile((fd_t)arg0);
        break;
    case ID_SkWriteFile:
        result = (status)SkWriteFile((fd_t)arg0, (char*)arg1, (int)arg2, (int)arg3);
        break;
    case ID_SkReadFile:
        result = (status)SkReadFile((fd_t)arg0, (char*)arg1, (int)arg2, (int)arg3);
        break;
    case ID_SkSeekFilePosition:
        result = (status)SkSeekFilePosition((fd_t)arg0, (int*)arg1);
        break;
    case ID_SkSeekMaxFilePosition:
        result = (status)SkSeekMaxFilePosition((fd_t)arg0, (int*)arg1);
        break;
    case ID_SkWriteConsole:
        result = (status)SkWriteConsole((char*)arg0, (int)arg1);
        break;
    case ID_SkReadConsole:
        result = (status)SkReadConsole((char**)arg0, (int*)arg1);
        break;
    case ID_SkAllocMemory:
        result = (status)SkAllocMemory((uint32_t)arg0, (void**)arg1);
        break;
    case ID_SkFreeMemory:
        result = (status)SkFreeMemory((void*)arg0);
        break;
    case ID_SkGetArgv:
        result = (status)SkGetArgv((char***)arg0);
        break;
    case ID_SkGetArgc:
        result = (status)SkGetArgc((int*)arg0);
        break;
    case ID_SkGetPid:
        result = (status)SkGetPid((pid_t*)arg0);
        break;
    case ID_SkTerminate:
        result = (status)SkTerminate((pid_t)arg0, (int*)arg1);
        break;
    case ID_SkCreateObject:
        result = (status)SkCreateObject((uuid_t*)arg0, (void**)arg1);
        break;
    case ID_SkDestroyObject:
        result = (status)SkDestroyObject((void**)arg0);
        break;
    case ID_SkDefineObject:
        result = (status)SkDefineObject((uuid_t*)arg0, (void**)arg1, (size_t)arg2);
        break;
    case ID_SkUndefineObject:
        result = (status)SkUndefineObject((uuid_t*)arg0);
        break;
    case ID_SkLockMutex:
        result = (status)SkLockMutex((int)arg0);
        break;
    case ID_SkUnlockMutex:
        result = (status)SkUnlockMutex((int)arg0);
        break;
    case ID_SkPushMessage:
        result = (status)SkPushMessage((pid_t)arg0, (int)arg1, (int)arg2, (int)arg3);
        break;
    case ID_SkPopMessage:
        result = (status)SkPopMessage((int*)arg0, (int*)arg1, (int*)arg2);
        break;
    case ID_SkCheckRemainingMessages:
        result = (int)SkCheckRemainingMessages();
        break;
    case ID_SkExecuteProcess:
        result = (status)SkExecuteProcess((const char*)arg0, (const char*)arg1, (const char*)arg2);
        break;
    case ID_SkGetLastProcessError:
        result = (status)SkGetLastProcessError();
        break;
    }

    ctx->eax = (uint32_t)result;
}