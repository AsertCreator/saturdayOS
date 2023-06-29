/*
    a lot of things here are written by Brandon Friesen
*/

#include "../include/system.h"

HeapObject system_heap;
char system_cmdline[512];

HeapObject BspMgrInitializeSystemHeap(void* at) {
    TtyMgrLog(SUCCESS, "bspmgr", "initializing heap...");

    HeapObject newheap;
    for (int i = 0; i < BIN_COUNT; i++)
        newheap.bins[i] = (HeapBinObject*)(at + sizeof(HeapBinObject) * i);
    HeapInitialize(&newheap, (uint32_t)at + sizeof(HeapBinObject) * BIN_COUNT);

    TtyMgrLog(SUCCESS, "bspmgr", "initialized heap");

    return newheap;
}

void BspMgrInitializeHAL() {
    TtyMgrLog(SUCCESS, "bspmgr", "initializing hal...");

#if ARCH == 0
    TtyMgrLog(SUCCESS, "bspmgr", "initializing gdt...");
    HALInitializeGDT();

    TtyMgrLog(SUCCESS, "bspmgr", "initializing idt...");
    HALInitializeIDT();
#endif

    TtyMgrLog(SUCCESS, "bspmgr", "initializing traps...");
    HALInitializeTraps();

    TtyMgrLog(SUCCESS, "bspmgr", "initializing irq...");
    HALInitializeInterrupts();

    // TtyMgrLog("bspmgr", "initializing paging...");
    // HALInitializePaging();

    TtyMgrLog(SUCCESS, "bspmgr", "initializing timer...");
    HALInitializeSystemTimer();

    TtyMgrLog(SUCCESS, "bspmgr", "initializing devmgr...");
    DevMgrInitialize();

    // human interaction interface
    if (HALInitializeHumanInteraction() != 0) {
        BspMgrIssuePanic("unexpected error occurred during hii initialization!");
    }

    HALEnableInterrupts();

    TtyMgrLog(SUCCESS, "bspmgr", "initialized hal");
}

void BspMgrInitializeEx() {
    TtyMgrLog(SUCCESS, "bspmgr", "initializing executive...");

    ExPrepareUsermode();
    ExSetupSyscalls();

    TtyMgrLog(SUCCESS, "bspmgr", "initialized executive...");
}

void BspMgrEntrypoint(struct multiboot_tag* header, uint32_t magic) {
    // nothing works there

    TtyMgrInitialize();
    // early tty works there

    TtyMgrLog(SUCCESS, "bspmgr", "satkrnl, version: %d.%d patch %d", SATKRNL_VERSION_MAJOR, SATKRNL_VERSION_MINOR, SATKRNL_VERSION_PATCH);

    if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
        // bootloader is not mb2 complaint. how dare it!
        TtyMgrLog(FAILED_NOTALLW, "bspmgr", "loaded by non-multiboot2 bootloader");
        HALForceReboot();
    }

    uint32_t addr = (uint32_t)header;
    struct multiboot_tag* tag;
    struct multiboot_tag_framebuffer* fb;
    struct multiboot_tag_string* str;
#define ARCH 1
#if ARCH == 1
    struct multiboot_tag_efi32* e32;
#endif

    for (tag = (struct multiboot_tag*)(addr + 8);
        tag->type != MULTIBOOT_TAG_TYPE_END;
        tag = (struct multiboot_tag*)((multiboot_uint8_t*)tag
            + ((tag->size + 7) & ~7))) {
        switch (tag->type)
        {
        case MULTIBOOT_TAG_TYPE_CMDLINE:
            str = (struct multiboot_tag_string*)tag;
            TtyMgrLog(SUCCESS, "bspmgr", "boot args: %s", str->string);
            StdCopyMemory(system_cmdline, str->string, StdStringLength(str->string) + 1);
            break;
        case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
            str = (struct multiboot_tag_string*)tag;
            TtyMgrLog(SUCCESS, "bspmgr", "booted by: %s", str->string);
            break;
        case MULTIBOOT_TAG_TYPE_EFI32:
#if ARCH == 0
            TtyMgrLog(FAILED_NOTIMPL, "bspmgr", "probably booted on uefi. make sure you are using correct kernel, cus this is bios kernel");
            HALHaltCPU();
#elif ARCH == 1
            e32 = (struct multiboot_tag_efi32*)tag;
#endif
            break;
        default:
            break;
        }
    }

#if ARCH == 1
    efi_system_table_t* st = (efi_system_table_t*)e32->pointer;
    st->ConOut->OutputString(st->ConsoleOutHandle, L"jk");
    for (;;);
#endif

    NEVER_REFERENCED(fb);

    system_heap = BspMgrInitializeSystemHeap((void*)(8 * 1024 * 1024));
    // heap works there

    // system is not initialized at this moment
    // almost every API is not working there

    BspMgrInitializeHAL();
    BspMgrInitializeEx();

    // system is somewhat intialized at this moment

    TtyMgrLog(SUCCESS, "bspmgr", "initializing shell...");

    // run init program here
    // ExStartProcess("FS0:/system/init");

    for (;;);

    TtyMgrLog(SUCCESS, "bspmgr", "starting shell...");

    // ExStartProcess("FS0:/system/sh");

    // shell is dead there, shutdown the system

    TtyMgrLog(SUCCESS, "bspmgr", "shutting down...");

    // ExStartProcess("FS0:/system/uninit");

    HALLateShutdown();

    for (;;);
}
