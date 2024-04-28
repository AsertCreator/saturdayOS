#include "include/panic.h"
#include "../hals/include/irq.h"
#include "../hals/include/tty.h"

void ExIssuePanic(const char* msg, uint32_t faultaddr, uint32_t errorcode) {
	printf("\n\n!!! panic, msg=\"%s\", faultaddr=%d, errorcode=%d, cpu=%d !!!\n", msg, faultaddr, errorcode, 0);
	printf("please reboot this device\n");
	ExHaltCPU();
}
void ExHaltCPU() {
	printf("cpu halted!\n");
	HALDisableInterrupts();
	while (1) { }
}