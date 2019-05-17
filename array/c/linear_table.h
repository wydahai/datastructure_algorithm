// 线性表C语言实现

#ifndef __LINEAR_TABLE_H__
#define __LINEAR_TABLE_H__

#define bool char
#define true 1
#define false 0

// 线性表的表示
typedef int ElemType;
typedef struct {
    ElemType *data;
    unsigned size;
    unsigned capacity;
}LinearTable;

bool Create(LinearTable *table, unsigned capacity);
unsigned Size(const LinearTable *table);
unsigned Capacity(const LinearTable *table);
bool Resize(LinearTable *table, unsigned capacity);
ElemType* GetElem(LinearTable *table, const unsigned idx);
bool InsertElem(LinearTable *table, unsigned idx, const ElemType *elem);
bool DeleteElem(LinearTable *table, const ElemType *elem);

#endif
