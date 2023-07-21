#pragma once
#include "../../include/system.h"

extern volatile uint64_t timer_ticks;
extern volatile uint64_t timer_secondspassed;

void HALTimerIRQHandler(RegisterContext* r);
void HALWaitTicks(uint64_t ticks);
void HALInitializeSystemTimer();