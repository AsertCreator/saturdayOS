#include "../include/syscall.h"

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

    if (log_syscalls)
        printf("syscall: id=%d, arg0=%d, arg1=%d, arg2=%d\n", id, arg0, arg1, arg2);

    switch (id) {
    case SYSCALL_WRITE:
        if ((int)arg0 == STDOUT || (int)arg0 == STDERR) {
            char* ch = (char*)arg1;
            if (arg2 == (uint32_t)-1) {
                // not using printf because if app would use format string there
                // unintentionally, printf will interpret this incorrectly and
                // probably will corrupt the stack
                for (int i = 0; ch[i] != 0; i++)
                    TtyMgrPutCharacter(ch[i]);
            }
            else {
                for (uint32_t i = 0; i < arg2; i++)
                    TtyMgrPutCharacter(ch[i]);
            }
            TtyMgrMoveCursor(tty_cursorx, tty_cursory);
        }
        break;
    case SYSCALL_READ:

        break;
    case SYSCALL_OPEN:

        break;
    case SYSCALL_UNRELIABLE:

        break;
    }
}