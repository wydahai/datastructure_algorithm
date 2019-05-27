/**
 * 题目：在O(1)时间删除链表节点
 * 描述：给定单向链表的头指针head和一个节点指针p，定义一个函数在O(1)时间删除该节点p。
 */

#include <iostream>
#include "linked_list.h"

void DeleteNode(ListNode **head, ListNode *deleted) {
    if (!head || !deleted) {
        return;
    }

    if (deleted->next_) {  // 删除的不是尾节点
        // 将deleted节点的后继节点值复制给deleted，然后删除直接后继
        ListNode *deleted_next = deleted->next_;
        deleted->value_ = deleted_next->value_;
        deleted->next_ = deleted_next->next_;
        delete deleted_next;
        deleted_next = nullptr;
    } else if (deleted == *head) {  // 删除的是尾节点且链表中只有一个节点
        delete deleted;
        *head = nullptr;
    } else {  // 删除的是尾节点，但链表中节点数量大于1
        ListNode *next = *head;
        while (next->next_ != deleted) { // 定位到deleted的直接前驱
            next = next->next_;
        }
        delete deleted;
        next->next_ = nullptr;
    }
}

int main() {
    ListNode *head = nullptr;
    DeleteNode(&head, nullptr);
    PrintList(head);

    head = new ListNode;
    head->value_ = 0;
    head->next_ = nullptr;
    DeleteNode(&head, head);
    PrintList(head);

    ListNode *node = head;
    ListNode *deleted = nullptr;
    for (int i=0; i<10; ++i) {
        ListNode *new_node = new ListNode;
        new_node->value_ = i;
        new_node->next_ = nullptr;
        if (i == 5) {
            deleted = new_node;
        }
        if (!node) {
            head = node = new_node;
        } else {
            node->next_ = new_node;
            node = new_node;
        }
    }
    DeleteNode(&head, deleted);
    PrintList(head);

    return 0;
}
