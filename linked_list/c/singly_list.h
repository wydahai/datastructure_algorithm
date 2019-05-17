#ifndef __SINGLY_LIST_H__
#define __SINGLY_LIST_H__

#ifndef ELEMENT_TYPE
#define ELEMENT_TYPE int
#endif

typedef struct SinglyListNode {
    ELEMENT_TYPE data_;
    struct SinglyListNode *next_;
}SinglyListNode;

// 创建一个单链表节点
typedef ELEMENT_TYPE (*Allocator)(ELEMENT_TYPE data);
SinglyListNode *AllocateNode(ELEMENT_TYPE data, Allocator alloc);
// 删除一个单链表节点
typedef void (*Dellocator)(ELEMENT_TYPE data);
void DellocateNode(SinglyListNode *node, Dellocator delloc);


// 创建带有头节点的单链表
SinglyListNode *CreateSinglyList();
// 销毁单链表
void DestroySinglyList(SinglyListNode *head, Dellocator delloc);
// 打印单链表中所有的元素
typedef void (*Printer)(const ELEMENT_TYPE data);
void PrintSinglyList(const SinglyListNode *head, Printer printer);

// 判断单链表是否为空
int Empty(const SinglyListNode *head);
// 获取单链表的长度：元素个数
unsigned Length(const SinglyListNode *head);

// 查找data对应的节点
SinglyListNode *Search(SinglyListNode *head, ELEMENT_TYPE data);

// 在指定节点前插入数据
int Insert(SinglyListNode *head, 
           SinglyListNode *node, 
           ELEMENT_TYPE data, 
           Allocator alloc);
int InsertToHead(SinglyListNode *head, ELEMENT_TYPE data, Allocator alloc);
int InsertToTail(SinglyListNode *head, ELEMENT_TYPE data, Allocator alloc);

int Delete(SinglyListNode *head, SinglyListNode *node, Dellocator delloc);
int DeleteFirst(SinglyListNode *head, Dellocator delloc);
int DeleteLast(SinglyListNode *head, Dellocator delloc);

#endif  // __SINGLY_LIST_H__
