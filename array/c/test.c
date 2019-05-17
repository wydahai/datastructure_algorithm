#include <stdio.h>

#include "linear_table.h"

void Print(LinearTable *table) {
    unsigned idx = 0;
    // 可以考虑将Size调用放到while循环外面，只需要
    // 一次调用，减少函数调用开销
    while (idx != Size(table)) {
        printf("%d ", *(GetElem(table, idx++)));
    }
    printf("\n");
}

int main() {
    LinearTable table;
    Create(&table, 5);
    printf("size: %u, capacity: %u\n", Size(&table), Capacity(&table));

    for (ElemType value=1; value<=5; ++value) {
        InsertElem(&table, 0, &value);
        printf("size: %u, capacity: %u\n", Size(&table), Capacity(&table));
    }
    ElemType value = 0;
    InsertElem(&table, Size(&table), &value);
    printf("size: %u, capacity: %u\n", Size(&table), Capacity(&table));
    value = 10;
    InsertElem(&table, 1, &value);
    printf("size: %u, capacity: %u\n", Size(&table), Capacity(&table));

    Print(&table);

    return 0;
}
