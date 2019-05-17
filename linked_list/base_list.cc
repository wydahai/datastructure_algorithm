#include <iostream>

#include "base_list.h"


// head一定是要一个指向指针的指针，这样当是空链表时才可以对其赋值
void AddToTail(LinkList *head, int value) {
    ListNode *new_node = new ListNode;
    new_node->value_ = value;
    new_node->next_ = nullptr;
    if (!*head) {
        *head = new_node;
    } else {
        ListNode *next = *head;
        while (next->next_) {  // 定位到最后一个节点
            next = next->next_;
        }
        next->next_ = new_node;
    }
}

void PrintList(const LinkList *head) {
    ListNode *node = *head;
    while (node) {
        std::cout << node->value_ << "->";
        node = node->next_;
    }
    std::cout << "nil" << std::endl;
}
