#include "../include/power.h"

void HALLateReboot() {
	// todo: implement normal reboot
	HALForceReboot();
}
void HALLateShutdown() {
	// todo: implement normal shutdown
	HALForceReboot();
}
void HALForceReboot() {
	idtp.limit = 0;
	idtp.base = 0;

	HALInstallLocalIDT();
	asm volatile ("int3");

	while (1);
}