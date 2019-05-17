#include <iostream>
#include <cassert>

#include "singly_list_c.h"


void PrintList(const ListNode *head) {
    assert(head);
    const ListNode *node= head->next_;
    while (node) {
        std::cout << node->data_ << "->";
        node = node->next_;
    }
    std::cout << "nil" << std::endl;
}

void InsertNode(ListNode *head, int data) {
    assert(head);
    ListNode *node = new ListNode;
    node->data_ = data;
    node->next_ = head->next_;
    head->next_ = node;
}


ListNode *SearchNode(ListNode *head, int data) {
    assert(head);
    ListNode *temp = head->next_;
    while (temp) {
        if (temp->data_ == data) {
            return temp;
        } else {
            temp = temp->next_;
        }
    }
    return nullptr;
}

// 传统方式删除：需要从头节点开始顺序查找，直至找到要删除
// 的节点，时间复杂度O(n)
void DeleteNode(ListNode *head, ListNode *node) {
    assert(head && node);
    ListNode *temp = head;
    while (temp->next_) {
        if (temp->next_ == node) {
            temp->next_ = node->next_;
            break;
        }
        temp = temp->next_;
    }
    delete node;
}

// 删除node，时间复杂度：O(1)
// 因为是单链表，当删除一个节点时，我们需要定位到待删除节点对前一个
// 节点，让前一个节点指向待删除节点对的后一个节点。因为是单链表，所
// 以我们不能通过待删除节点直接定位到前一个节点，但是我们可以定位到
// 后一个节点，所以此时可以将后一个节点的值复制到待删除节点，然后删
// 除后一个节点，也能达到删除该节点（值）的目的
// 假如要删除的节点是最后一个节点，上面就无法实现，还是需要遍历到最
// 后一个节点进行删除
void DeleteNodeV2(ListNode *head, ListNode *node) {
    assert(head && node);
    if (node->next_) {  // 要删除到节点不是链表中最后一个节点
        ListNode *next = node->next_;
        node->data_ = next->data_;
        node->next_ = next->next_;
        delete next;  // 实际删除到是node的后继节点，但是值已经复制到node中
    } else {
        ListNode *next = head;
        while (next && next->next_!=node) {
            next = next->next_;
        }
        next->next_ = nullptr;
        delete node;
    }
}
