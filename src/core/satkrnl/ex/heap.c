#include "../include/system.h"

void HeapInitialize(HeapObject* heap, long start) {
    HeapNodeObject* init_region = (HeapNodeObject*)start;
    init_region->hole = 1;
    init_region->size = (HEAP_INIT_SIZE)-sizeof(HeapNodeObject) - sizeof(HeapFooterObject);

    HeapCreateFoot(init_region);

    HeapAddNode(heap->bins[HeapGetBinIndex(init_region->size)], init_region);

    heap->start = start;
    heap->end = start + HEAP_INIT_SIZE;
}

void* HeapAlloc(HeapObject* heap, size_t size) {
    uint32_t index = HeapGetBinIndex(size);
    HeapBinObject* temp = (HeapBinObject*)heap->bins[index];
    HeapNodeObject* found = HeapGetBestFit(temp, size);

    while (found == NULL) {
        if (index + 1 >= BIN_COUNT) {
            return NULL;
        }

        temp = heap->bins[++index];
        found = HeapGetBestFit(temp, size);
    }

    if ((found->size - size) > (overhead + MIN_ALLOC_SZ)) {
        HeapNodeObject* split = (HeapNodeObject*)(((char*)found + sizeof(HeapNodeObject) + sizeof(HeapFooterObject)) + size);
        split->size = found->size - size - sizeof(HeapNodeObject) - sizeof(HeapFooterObject);
        split->hole = 1;

        HeapCreateFoot(split);

        uint32_t new_idx = HeapGetBinIndex(split->size);

        HeapAddNode(heap->bins[new_idx], split);

        found->size = size;
        HeapCreateFoot(found);
    }

    found->hole = 0;
    HeapRemoveNode(heap->bins[index], found);

    found->prev = NULL;
    found->next = NULL;
    return &found->next;
}

void HeapFree(HeapObject* heap, void* p) {
    HeapBinObject* list;
    HeapFooterObject* new_foot, * old_foot;

    HeapNodeObject* head = (HeapNodeObject*)((char*)p - 8);
    if (head == (HeapNodeObject*)(uintptr_t)heap->start) {
        head->hole = 1;
        HeapAddNode(heap->bins[HeapGetBinIndex(head->size)], head);
        return;
    }

    HeapNodeObject* next = (HeapNodeObject*)((char*)HeapGetFoot(head) + sizeof(HeapFooterObject));
    HeapFooterObject* f = (HeapFooterObject*)((char*)head - sizeof(HeapFooterObject));
    HeapNodeObject* prev = f->header;

    if (prev->hole) {
        list = heap->bins[HeapGetBinIndex(prev->size)];
        HeapRemoveNode(list, prev);

        prev->size += overhead + head->size;
        new_foot = HeapGetFoot(head);
        new_foot->header = prev;

        head = prev;
    }

    if (next->hole) {
        list = heap->bins[HeapGetBinIndex(next->size)];
        HeapRemoveNode(list, next);

        head->size += overhead + next->size;

        old_foot = HeapGetFoot(next);
        old_foot->header = 0;
        next->size = 0;
        next->hole = 0;

        new_foot = HeapGetFoot(head);
        new_foot->header = head;
    }

    head->hole = 1;
    HeapAddNode(heap->bins[HeapGetBinIndex(head->size)], head);
}

uint32_t HeapGetBinIndex(size_t sz) {
    uint32_t index = 0;
    sz = sz < 4 ? 4 : sz;

    while (sz >>= 1) index++;
    index -= 2;

    if (index > BIN_MAX_IDX) index = BIN_MAX_IDX;
    return index;
}

void HeapCreateFoot(HeapNodeObject* head) {
    HeapFooterObject* foot = HeapGetFoot(head);
    foot->header = head;
}

HeapFooterObject* HeapGetFoot(HeapNodeObject* node) {
    return (HeapFooterObject*)((char*)node + sizeof(HeapNodeObject) + node->size);
}

HeapNodeObject* HeapGetWilderness(HeapObject* heap) {
    HeapFooterObject* wild_foot = (HeapFooterObject*)((char*)heap->end - sizeof(HeapFooterObject));
    return wild_foot->header;
}