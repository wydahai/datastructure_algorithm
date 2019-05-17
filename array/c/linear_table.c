#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linear_table.h"

bool Create(LinearTable *table, unsigned capacity) {
    assert(table);
#if 0
    table->data = (ElemType*)malloc(capacity*sizeof(ElemType));
#else
    table->data = (ElemType*)calloc(capacity, sizeof(ElemType));
#endif
    if (!table->data) {
        return false;
    }
    table->capacity = capacity;
    table->size = 0;
    return true;
}

unsigned Size(const LinearTable *table) {
    assert(table);
    return table->size;
}

unsigned Capacity(const LinearTable *table) {
    assert(table);
    return table->capacity;
}

ElemType* GetElem(LinearTable *table, const unsigned idx) {
    assert(table);
    if (idx >= table->size) {
        return NULL;
    }
    return &(table->data[idx]);
}

bool Resize(LinearTable *table, unsigned capacity) {
    assert(table);
    ElemType *tmp = (ElemType*)realloc(table->data, capacity);
    if (!tmp) {
        return false;
    }
    table->data = tmp;
    table->capacity = capacity;
    return true;
}

// 只允许在0 - size（包括size，表示在尾部追加）范围内插入
bool InsertElem(LinearTable *table, unsigned idx, const ElemType *elem) {
    assert(table);
    if (idx > table->size) {
        return false;
    }
    if (table->size == table->capacity) {
        if (!Resize(table, 2*table->capacity)) {
            return false;
        }
    }
    // 若不再表尾插入，则需要后移元素
    if (idx < table->size) {
        for (long k=table->size-1; k>=idx; --k) {
            table->data[k+1] = table->data[k];
        }
    }
    table->data[idx] = *elem;  // 插入新的元素
    ++table->size;
    return true;
}
