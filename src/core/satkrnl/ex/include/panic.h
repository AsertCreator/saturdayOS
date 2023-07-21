#pragma once
#include "../../include/system.h"

void ExIssuePanic(const char* msg, uint32_t faultaddr);
void ExHaltCPU();