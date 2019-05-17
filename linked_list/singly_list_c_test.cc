#include <iostream>
#include "singly_list_c.h"

int main() {
    ListNode singly;
    for (int i=0; i!=10; ++i) {
        InsertNode(&singly, i+1);
    }
    PrintList(&singly);

    int data = 11;
    ListNode *node = SearchNode(&singly, data);
    if (!node) {
        std::cout << "no data: " << data 
            << " in singly link list" << std::endl;
    }

    data = 5;
    node = SearchNode(&singly, data);
    DeleteNode(&singly, node);
    PrintList(&singly);

    data = 10;
    node = SearchNode(&singly, data);
    DeleteNode(&singly, node);
    PrintList(&singly);

    data = 1;
    node = SearchNode(&singly, data);
    DeleteNode(&singly, node);
    PrintList(&singly);

    data = 4;
    node = SearchNode(&singly, data);
    DeleteNodeV2(&singly, node);
    PrintList(&singly);

    data = 9;
    node = SearchNode(&singly, data);
    DeleteNodeV2(&singly, node);
    PrintList(&singly);

    data = 2;
    node = SearchNode(&singly, data);
    DeleteNodeV2(&singly, node);
    PrintList(&singly);

    return 0;
}

