#include "../include/debug.h"

void DbgPrintStacktrace() {
    /*
	uint32_t* rebp = 0;
    uint32_t* reip = 0;

    asm volatile ("movl $ebp, %0" : "=r"(rebp) :);

    while (rebp != (uint32_t*)0) {
        reip = (uint32_t*)rebp[1];

        printf("    at %x\n", reip);

        rebp = (uint32_t*)*rebp;
    }
    */

    // it should've been working, but it doesn't
    // so fuk it
}