#include "../include/init.h"
#include "../include/irq.h"
#include "../include/pci.h"
#include "../include/hii.h"
#include "../include/tty.h"
#include "../include/port.h"
#include "../include/paging.h"
#include "include/gdt.h"
#include "include/idt.h"
#include "include/isrs.h"
#include "../../ex/include/panic.h"

void HALInitialize() {
    ENTER_CRITICAL_ZONE;

    TtyMgrLog(SUCCESS, "hal", "initializing hal...");

    TtyMgrLog(SUCCESS, "hal", "initializing gdt...");
    HALInitializeGDT();

    TtyMgrLog(SUCCESS, "hal", "initializing idt...");
    HALInitializeIDT();

    TtyMgrLog(SUCCESS, "hal", "initializing traps...");
    HALInitializeTraps();

    TtyMgrLog(SUCCESS, "hal", "initializing irq...");
    HALInitializeInterrupts();

    TtyMgrLog(SUCCESS, "hal", "initializing paging...");
    HALInitializePaging();

    TtyMgrLog(SUCCESS, "hal", "initializing pci...");
    HALPciScanEverything();

    // human interaction interface
    if (HALInitializeHumanInteraction() != 0) {
        ExIssuePanic("unexpected error occurred during hii initialization!", 0, 0);
    }

    LEAVE_CRITICAL_ZONE;

    TtyMgrLog(SUCCESS, "hal", "initialized hal");
}