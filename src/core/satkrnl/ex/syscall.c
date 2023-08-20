#include "../hals/include/syscall.h"

int SkGetOSVersion() {
    return 0x00030000;
}
char* SkGetErrorMessage(status err) {
    switch (err) {
    case SUCCESS: return "Operation succedded";
    case FAILED_GENERAL: return "Operation has failed";
    case FAILED_NOTIMPL: return "Device or feature not implemented";
    case FAILED_NOTALLW: return "Access denied";
    case FAILED_NOTAVAL: return "Device, file or feature is not available";
    case FAILED_NOTRESP: return "Device or file is not responding";
    case FAILED_UNREACH: return "Device, file or feature is unreachable";
    case FAILED_NOTFUND: return "Device, file or feature is not found";
    case FAILED_OUTOFMM: return "Process ran out of memory";
    case FAILED_SKIPPED: return "System prematurely stopped the operation";
    case FAILED_BADREQT: return "Process sent invalid request";
    case FAILED_BADRESP: return "Device or feature sent unprocessable response";
    default: return "Unknown error";
    }
}
status SkListDir(char* path, /*out*/ char*** els) {
    NEVER_REFERENCED(path);
    NEVER_REFERENCED(els);
    return FAILED_NOTIMPL;
}
status SkCreateDir(char* path) {
    NEVER_REFERENCED(path);
    return FAILED_NOTIMPL;
}
status SkCreateFile(char* path) {
    NEVER_REFERENCED(path);
    return FAILED_NOTIMPL;
}
status SkDeleteDir(char* path) {
    NEVER_REFERENCED(path);
    return FAILED_NOTIMPL;
}
status SkDeleteFile(char* path) {
    NEVER_REFERENCED(path);
    return FAILED_NOTIMPL;
}
status SkOpenFile(char* path, char mode, /*out*/ fd_t* fd) {
    NEVER_REFERENCED(path);
    NEVER_REFERENCED(mode);
    NEVER_REFERENCED(fd);
    return FAILED_NOTIMPL;
}
status SkCloseFile(fd_t fd) {
    NEVER_REFERENCED(fd);
    return FAILED_NOTIMPL;
}
status SkWriteFile(fd_t fd, char* ch, int ix, int sz) {
    NEVER_REFERENCED(fd);
    NEVER_REFERENCED(ch);
    NEVER_REFERENCED(ix);
    NEVER_REFERENCED(sz);
    return FAILED_NOTIMPL;
}
status SkReadFile(fd_t fd, /*out*/ char* buf, int ix, int sz) {
    NEVER_REFERENCED(fd);
    NEVER_REFERENCED(buf);
    NEVER_REFERENCED(ix);
    NEVER_REFERENCED(sz);
    return FAILED_NOTIMPL;
}
status SkSeekFilePosition(fd_t fd, /*out*/ int* out) {
    NEVER_REFERENCED(fd);
    NEVER_REFERENCED(out);
    return FAILED_NOTIMPL;
}
status SkSeekMaxFilePosition(fd_t fd, /*out*/ int* out) {
    NEVER_REFERENCED(fd);
    NEVER_REFERENCED(out);
    return FAILED_NOTIMPL;
}
status SkWriteConsole(char* str, int am) {
    int totallen = 0;

    if (am == -1) totallen = StdStringLength(str);
    else if (am == 0) return SUCCESS;
    else if (am < 0) return FAILED_SKIPPED;

    for (int i = 0; i < totallen; i++)
        TtyMgrPutCharacter(str[i]);

    TtyMgrMoveCursor(tty_cursorx, tty_cursory);

    return SUCCESS;
}
status SkReadConsole(/*out*/ char** buf, /*out*/ int* c) {
    NEVER_REFERENCED(buf);
    NEVER_REFERENCED(c);
    return FAILED_NOTIMPL;
}
status SkAllocMemory(uint32_t sz, /*out*/ void** out) {
    void* mem = HeapAlloc(&system_heap, sz);
    if (mem) return FAILED_OUTOFMM;
    *out = mem;
    return SUCCESS;
}
status SkFreeMemory(void* mem) {
    HeapFree(&system_heap, mem);
    return SUCCESS;
}
status SkGetArgv(/*out*/ char*** out) {
    NEVER_REFERENCED(out);
    return FAILED_NOTIMPL;
}
status SkGetArgc(/*out*/ int* out) {
    NEVER_REFERENCED(out);
    return FAILED_NOTIMPL;
}
status SkGetPid(/*out*/ pid_t* out) {
    if (out == 0) return FAILED_BADREQT;
    return FAILED_NOTIMPL;
}
status SkTerminate(pid_t pid, /*out*/ int* out) {
    NEVER_REFERENCED(pid);
    NEVER_REFERENCED(out);
    return FAILED_NOTIMPL;
}
status SkCreateObject(uuid_t* objid, void** out) {
    NEVER_REFERENCED(objid);
    NEVER_REFERENCED(out);
    return FAILED_NOTIMPL;
}
status SkDestroyObject(void** in) {
    NEVER_REFERENCED(in);
    return FAILED_NOTIMPL;
}
status SkDefineObject(uuid_t* objid, void** in, size_t sz) {
    NEVER_REFERENCED(objid);
    NEVER_REFERENCED(in);
    NEVER_REFERENCED(sz);
    return FAILED_NOTIMPL;
}
status SkUndefineObject(uuid_t* objid) {
    NEVER_REFERENCED(objid);
    return FAILED_NOTIMPL;
}
status SkLockMutex(int mutexid) {
    NEVER_REFERENCED(mutexid);
    return FAILED_NOTIMPL;
}
status SkUnlockMutex(int mutexid) {
    NEVER_REFERENCED(mutexid);
    return FAILED_NOTIMPL;
}
status SkExecuteProcess(const char* path, const char* args, const char* env) {
    NEVER_REFERENCED(path);
    NEVER_REFERENCED(args);
    NEVER_REFERENCED(env);
    return FAILED_NOTIMPL;
}
status SkGetLastProcessError() {
    return FAILED_NOTIMPL;
}
status SkPushMessage(pid_t pid, int msg, int arg0, int arg1) {
    NEVER_REFERENCED(pid);
    NEVER_REFERENCED(msg);
    NEVER_REFERENCED(arg0);
    NEVER_REFERENCED(arg1);
    return FAILED_NOTIMPL;
}
status SkPopMessage(int* msg, int* arg0, int* arg1) {
    NEVER_REFERENCED(msg);
    NEVER_REFERENCED(arg0);
    NEVER_REFERENCED(arg1);
    return FAILED_NOTIMPL;
}
int SkCheckRemainingMessages() {
    return 0;
}