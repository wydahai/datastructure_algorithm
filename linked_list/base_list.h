#ifndef __BASE_LIST_H__
#define __BASE_LIST_H__


struct ListNode {  // 单链表节点定义
    int value_;
    ListNode *next_;
};

using LinkList = ListNode *;


void AddToTail(LinkList *head, int value);
void PrintList(const LinkList *head);

#endif
