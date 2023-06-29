#pragma once
#include "../../include/system.h"

status HALCreateStandaloneThread(const char* name, ThreadEntry entry, uint32_t stacksize, /*out*/ ThreadObject** out);
void HALLoadContext(RegisterContext curctx);