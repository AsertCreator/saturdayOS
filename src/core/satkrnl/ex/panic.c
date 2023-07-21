#include "include/panic.h"

void ExIssuePanic(const char* msg, uint32_t faultaddr) {
	printf("\n\n!!! panic, msg=\"%s\", faultaddr=%x, cpu=%d !!!\n", msg, faultaddr, 0);
	printf("please reboot this device\n");
	ExHaltCPU();
}
void ExHaltCPU() {
	printf("cpu halted!\n");
	HALDisableInterrupts();
	while (1) { }
}