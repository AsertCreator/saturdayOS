#include "../include/paging.h"

uint32_t page_directory[PAGE_DIR_SIZE] __attribute__((aligned(4096)));
uint32_t page_table[PAGE_TBL_SIZE][PAGE_DIR_SIZE] __attribute__((aligned(4096)));

void HALInitializePaging() {
    // identity page entire memory
    int j = 0;
    for (int i = 0; i < PAGE_DIR_SIZE; i++) {
        for (; j < PAGE_TBL_SIZE; j++) {
            page_table[i][j] = (j * 0x1000) | 3;
            j++;
        }
        page_directory[i] = (uint32_t)&(page_table[i]) | 3;
    }

    HALLoadCR3((uint32_t)page_directory);
    HALStartupPaging();
}
void HALMap(void* physaddr, void* virtualaddr, int flags) {
    int ptindex = (uint32_t)physaddr / 0x1000;
    int pdindex = ptindex / 1024;
    page_table[pdindex][ptindex] = (uint32_t)virtualaddr | flags | 3;
}
void* HALGetVirtualAddress(void* physaddr) {
    int ptindex = (uint32_t)physaddr / 0x1000;
    int pdindex = ptindex / 1024;
    return (void*)(page_table[pdindex][ptindex] & 0xFFFFF000);
}