#pragma once
#include "../../include/system.h"

void ExIssuePanic(const char* msg, uint32_t faultaddr, uint32_t errorcode);
void ExHaltCPU();