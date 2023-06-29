#pragma once
#include "../../include/system.h"

typedef void (*usermode_func)(void);

void ExPrepareUsermode();
void ExRunInUsermode(usermode_func func);