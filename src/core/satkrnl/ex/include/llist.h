#pragma once
#include "heap.h"
#include "../../include/system.h"

void HeapAddNode(HeapBinObject* bin, HeapNodeObject* node);
void HeapRemoveNode(HeapBinObject* bin, HeapNodeObject* node);
HeapNodeObject* HeapGetBestFit(HeapBinObject* list, size_t size);
HeapNodeObject* HeapGetLastNode(HeapBinObject* list);