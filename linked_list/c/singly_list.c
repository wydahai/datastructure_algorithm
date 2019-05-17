#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "singly_list.h"


SinglyListNode *AllocateNode(ELEMENT_TYPE data, Allocator alloc) {
    SinglyListNode *node = (SinglyListNode*)malloc(sizeof(SinglyListNode));
    if (node == NULL) {
        return NULL;
    }
    node->data_ = alloc?alloc(data):data;
    node->next_ = NULL;
    return node;
}

void DellocateNode(SinglyListNode *node, Dellocator delloc) {
    if (node) {
        if (delloc) {
            delloc(node->data_);
        }
        free(node);
    }
}

SinglyListNode *CreateSinglyList() {
    SinglyListNode *head = (SinglyListNode*)malloc(sizeof(SinglyListNode));
    if (head) {
        head->next_ = NULL;
    }
    return head;
}

void DestroySinglyList(SinglyListNode *head, Dellocator delloc) {
    assert(head);
    SinglyListNode *node = NULL;
    while (head->next_) {
        node = head->next_;
        head->next_ = node->next_;
        DellocateNode(node, delloc);
    }
    free(head);
}

void PrintSinglyList(const SinglyListNode *head, Printer printer) {
    assert(head);
    const SinglyListNode *node = head;
    while ((node=node->next_)) {
        printer(node->data_);
    }
}

int Empty(const SinglyListNode *head) {
    assert(head);
    return head->next_?0:1;
}

unsigned Length(const SinglyListNode *head) {
    assert(head);
    unsigned length = 0;
    const SinglyListNode *node = head;
    while ((node=node->next_)) {
        ++length;
    }
    return length;
}

SinglyListNode *Search(SinglyListNode *head, ELEMENT_TYPE data) {
    assert(head);
    SinglyListNode *node = head;
    while ((node=node->next_)) {
        if (node->data_ == data) {
            break;
        }
    }
    return node;
}

// 传统方法：首先在链表中定位到要插入位置的前一个节点，时间复杂度：O(n)
static int InsertV1(SinglyListNode *head, 
                    SinglyListNode *node, 
                    ELEMENT_TYPE data, 
                    Allocator alloc) {
    assert(head);
    SinglyListNode *next = head;
    while ((next->next_!=node) && (next=next->next_)) {
        ;
    }
    if (!next) {  // 没有找到node节点
        return -1;
    }
    SinglyListNode *new_node = AllocateNode(data, alloc);
    if (!new_node) {
        return -1;
    }
    new_node->next_ = next->next_;
    next->next_ = new_node;
    return 0;
}

// 改进：在单链表中，若想要在某个节点之前插入新的节点，则需要
// 直到该节点的直接前驱节点，使前驱节点的next指向新的节点，新
// 节点的next指向插入位置节点
static int InsertV2(SinglyListNode *head, 
                    SinglyListNode *node, 
                    ELEMENT_TYPE data, 
                    Allocator alloc) {
    assert(head);
    SinglyListNode *new_node = AllocateNode(data, alloc);    
    if (!new_node) {
        return -1;
    }
    if (!node) {  // 尾部插入
        SinglyListNode *next = head;
        while (next->next_) {
            next = next->next_;
        }
        next->next_ = new_node;
    } else {  // 表头或中间插入
        new_node->data_ = node->data_;
        node->data_ = data;
        new_node->next_ = node->next_;
        node->next_ = new_node;
    }
    return 0;
}

int Insert(SinglyListNode *head, 
           SinglyListNode *node, 
           ELEMENT_TYPE data, 
           Allocator alloc) {
#ifdef TRADITIONAL
    return InsertV1(head, node, data, alloc);
#else
    return InsertV2(head, node, data, alloc);
#endif
}

int InsertToHead(SinglyListNode *head, ELEMENT_TYPE data, Allocator alloc) {
    assert(head);
    return Insert(head, head->next_, data, alloc);
}

int InsertToTail(SinglyListNode *head, ELEMENT_TYPE data, Allocator alloc) {
    assert(head);
    return Insert(head, NULL, data, alloc);
}

// 传统方法：首先定位到要删除节点到前驱节点，然后再进行删除，时间复杂度：O(n)
static int DeleteV1(SinglyListNode *head, 
                    SinglyListNode *node, 
                    Dellocator delloc) {
    assert(head && node);
    SinglyListNode *prev = head;
    while ((prev->next_!=node) && (prev=prev->next_)) {
        ;
    }
    if (!prev) {
        return -1;
    }
    prev->next_ = node->next_;
    DellocateNode(node, delloc);
    return 0;
}

// 改进方法：不去定位要删除的节点，而是将后继节点的值复制到要删除的节点，
// 然后删除后继节点，这样就减少了定位的性能消耗，时间复杂度：O(1)
static int DeleteV2(SinglyListNode *head, 
                    SinglyListNode *node, 
                    Dellocator delloc) {
    assert(head && node);
    if (!node->next_) {  // 如果要删除的节点是最后一个节点，则没有后继，需要遍历
        // 定位最后一个节点的前驱节点
        SinglyListNode *prev = head;
        while ((prev->next_!=node) && (prev=prev->next_)) {
            ;
        }
        if (!prev) {
            return -1;
        }
        prev->next_ = NULL;
        DellocateNode(node, delloc);
    } else {
        SinglyListNode *next = node->next_;
        next->data_ = node->data_;
        node->next_ = next->next_;
        DellocateNode(next, delloc);
    }
    return 0;
}

int Delete(SinglyListNode *head, SinglyListNode *node, Dellocator delloc) {
    assert(head && node);
#ifdef TRADITIONAL
    return DeleteV1(head, node, delloc);
#else
    return DeleteV2(head, node, delloc);
#endif
}

int DeleteFirst(SinglyListNode *head, Dellocator delloc) {
    assert(head);
    if (!head->next_) {
        return -1;
    }
    return Delete(head, head->next_, delloc);
}

int DeleteLast(SinglyListNode *head, Dellocator delloc) {
    assert(head);
    if (!head->next_) {
        return -1;
    }
    // 首先定位到最后一个节点，不需要调用Delete，因为调用Delete还需要再次
    // 定位last节点
    SinglyListNode *last_prev = head;
    while (last_prev->next_->next_) {
        last_prev = last_prev->next_;
    }
    DellocateNode(last_prev->next_, delloc);
    last_prev->next_ = NULL;
    return 0;
}
