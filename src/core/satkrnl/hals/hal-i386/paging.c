#include "../include/paging.h"

uint32_t page_directory[PAGE_DIR_SIZE] __attribute__((aligned(4096)));
uint32_t page_table[PAGE_TBL_SIZE][PAGE_DIR_SIZE] __attribute__((aligned(4096)));

static void IdentityMap(uint32_t* first_pte, uint32_t from, uint32_t size) {
    from = from & 0xfffff000; // discard bits we don't want
    for (; size > 0; from += 4096, size -= 4096, first_pte++) {
        *first_pte = from | 1;     // mark page present.
    }
}

void HALInitializePaging() {
    int j = 0;
    for (int i = 0; i < PAGE_DIR_SIZE; i++) {
        for (; j < PAGE_TBL_SIZE; j++) {
            page_table[i][j] = (j * 0x1000) | 3;
            j++;
        }
        page_directory[i] = (uint32_t)&(page_table[i]) | 3;
    }

    IdentityMap(&(page_table[0][0]), 0, 64 * 1024 * 1024);

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