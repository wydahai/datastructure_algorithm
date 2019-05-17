/**
 * NOTE：对于ELEMENT_TYPE为指针类型时未测试
 */
#include <stdio.h>

// 如果要想改变默认的int类型，需要在此处定义宏：ELEMENT_TYPE
#include "singly_list.h"

void PrintDividor(const char *msg) {
    printf("\n********** %s **********\n", msg);
}

void PrintList(const ELEMENT_TYPE data) {
    printf("%d->", data);
}

void TestEmptyList() {
    PrintDividor(__func__);

    SinglyListNode *singly = CreateSinglyList();
    PrintSinglyList(singly, PrintList);
    printf("\n");
    printf("list_length: %u\n", Length(singly));
    printf("list_empty: %s\n", Empty(singly)?"true":"false");
    int data = 10;
    SinglyListNode *node = Search(singly, data);
    if (!node) {
        printf("there is no node for data: %d\n", data);
    }
    DestroySinglyList(singly, NULL);
}

void TestNotEmptyList() {
    PrintDividor(__func__);

    SinglyListNode *singly = CreateSinglyList();
    for (int i=10; i>0; --i) {
        InsertToHead(singly, i, NULL);
    }

    int data = 5;
    SinglyListNode *node = Search(singly, data);
    if (!node) {
        printf("there is no node for data: %d\n", data);
    } else {
        Insert(singly, node, 15, NULL);
    }
    // 在尾部插入一个节点
    InsertToTail(singly, 11, NULL);

    Delete(singly, node, NULL);
    DeleteFirst(singly, NULL);
    DeleteLast(singly, NULL);

    PrintSinglyList(singly, PrintList);
    printf("\n");
    printf("list_length: %u\n", Length(singly));
    printf("list_empty: %s\n", Empty(singly)?"true":"false");
    DestroySinglyList(singly, NULL);
}

int main() {
    TestEmptyList();
    TestNotEmptyList();

    return 0;
}
