#pragma once
#include "../../include/system.h"

#define HEAP_INIT_SIZE 0x10000
#define HEAP_MAX_SIZE 0x100000
#define HEAP_MIN_SIZE 0x10000

#define MIN_ALLOC_SZ 4

#define MIN_WILDERNESS 0x2000
#define MAX_WILDERNESS 0x1000000

#define BIN_COUNT 9
#define BIN_MAX_IDX (BIN_COUNT - 1)

// HeapNodeObject "<-" SystemObject
typedef struct HeapNodeObject {
    uint32_t hole;
    uint32_t size;
    struct HeapNodeObject* next;
    struct HeapNodeObject* prev;
} HeapNodeObject;

// HeapFooterObject "<-" SystemObject
typedef struct {
    HeapNodeObject* header;
} HeapFooterObject;

// HeapBinObject "<-" SystemObject
typedef struct {
    HeapNodeObject* head;
} HeapBinObject;

// HeapObject "<-" SystemObject
typedef struct {
    long start;
    long end;
    HeapBinObject* bins[BIN_COUNT];
} HeapObject;

#define overhead sizeof(HeapFooterObject) + sizeof(HeapNodeObject)

void HeapInitialize(HeapObject* heap, long start);

void* HeapAlloc(HeapObject* heap, size_t size);
void HeapFree(HeapObject* heap, void* p);

uint32_t HeapGetBinIndex(size_t sz);
void HeapCreateFoot(HeapNodeObject* head);
HeapFooterObject* HeapGetFoot(HeapNodeObject* head);

HeapNodeObject* HeapGetWilderness(HeapObject* heap);