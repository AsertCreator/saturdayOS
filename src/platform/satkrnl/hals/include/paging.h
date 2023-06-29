#pragma once
#include "../../include/system.h"
#define PAGE_DIR_SIZE 1024
#define PAGE_TBL_SIZE 1024

void HALLoadCR3(uint32_t val);
void HALStartupPaging();
void HALInitializePaging();
void HALMap(void* physaddr, void* virtualaddr, int flags);
void* HALGetVirtualAddress(void* physaddr);