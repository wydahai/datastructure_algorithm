#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <iostream>

struct ListNode {
    int value_;
    ListNode *next_;
};

void PrintList(const ListNode *head) {
    const ListNode *node = head;
    while (node) {
        std::cout << node->value_ << "->";
        node = node->next_;
    }
    std::cout << "nil" << std::endl;
}

#endif  // __LINKED_LIST_H__
