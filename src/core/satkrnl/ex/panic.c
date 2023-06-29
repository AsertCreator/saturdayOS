#include "include/panic.h"

void BspMgrIssuePanic(const char* msg) {
	TtyMgrLog(FAILED_GENERAL, "hal", "\n\n!!! panic, msg=\"%s\", cpu=%d !!!", msg, 0);
	TtyMgrLog(FAILED_GENERAL, "hal", "please reboot this device");
	HALHaltCPU();
}
void HALHaltCPU() {
	TtyMgrLog(FAILED_GENERAL, "hal", "cpu halted!");
	HALDisableInterrupts();
	while (1) { }
}