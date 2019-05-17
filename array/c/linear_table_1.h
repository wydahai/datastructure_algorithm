#ifndef __LINEAR_TABLE_1_H__
#define __LINEAR_TABLE_1_H__

typedef struct {
    void* data;
    unsigned elemSize;
    unsigned size;
    unsigned capacity;
}LinearTable;

#endif
