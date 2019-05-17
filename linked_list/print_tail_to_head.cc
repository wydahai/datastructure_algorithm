/**
 * 题目：从尾到头打印单链表
 * 描述：实现一个函数，输入一个单链表的头结点，从尾到头反过来打印出每个结点的值
 * 解答：1.可以通过栈来实现-先进后出
 */

#include <iostream>
#include <stack>

#include "base_list.h"


// 利用栈的特性：先进后出
void PrintListReveringly(const LinkList *head) {
    std::stack<ListNode*> nodes;
    ListNode *node = *head;
    // 单链表只能从表头到尾部的顺序进行遍历，所以利用栈的先进后出特性
    // 来将node压栈，这样在输出时就获得了反方向输出
    while (node) {
        nodes.push(node);
        node = node->next_;
    }
    while (!nodes.empty()) {
        std::cout << nodes.top()->value_ << "->";
        nodes.pop();
    }
    std::cout << "nil" << std::endl;
}


// 递归本质上就是一个栈结构，所以可以直接进行递归，使用递归的缺点：
// 1.当递归层次很深时可能会导致栈溢出；
// 2.递归涉及到压栈、弹栈等操作，性能会比较低
void PrintListRecusively(const ListNode *head) {
    if (!head) {
        return;
    }
    PrintListRecusively(head->next_);
    std::cout << head->value_ << "->";
}


int main() {
    LinkList linked = nullptr;
    for (int i=0; i<10; ++i) {
        AddToTail(&linked, i);
    }
    PrintList(&linked);

    PrintListReveringly(&linked);
    PrintListRecusively(linked);

    return 0;
}
