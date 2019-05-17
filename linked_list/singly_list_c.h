#ifndef __DATA_STRUCTURE_SINGLY_LIST_C_H__
#define __DATA_STRUCTURE_SINGLY_LIST_C_H__

struct ListNode {
    int data_;
    ListNode *next_;
};

void CreateList();
void InsertNode(ListNode *head, int data);
ListNode *SearchNode(ListNode *head, int data);

void DeleteNode(ListNode *head, ListNode *node);
void DeleteNodeV2(ListNode *head, ListNode *node);

void PrintList(const ListNode *head);

#endif  // __DATA_STRUCTURE_SINGLY_LIST_C_H__
