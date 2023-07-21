#include "../include/timer.h"

volatile uint64_t timer_ticks = 0;
volatile uint64_t timer_secondspassed = 0;

void HALTimerIRQHandler(RegisterContext *r) {
    NEVER_REFERENCED(r);
    timer_ticks++;
    if (timer_ticks % 18 == 0) {
        timer_secondspassed++;
    }
}

void HALWaitTicks(uint64_t ticks) {
    uint64_t eticks = timer_ticks + ticks;
    while (timer_ticks < eticks) {}
}

void HALInitializeSystemTimer() {
    HALSetIRQHandler(0, HALTimerIRQHandler);
}
