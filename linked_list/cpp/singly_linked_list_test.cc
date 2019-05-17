#include <iostream>

#include "singly_linked_list.h"

int main() {
    SLinkedList<int> some;
    SLinkedList<int> singly = std::move(some);

    singly.Insert(0, 10);
    int value = 9;
    singly.Insert(0, std::move(value));
    value = 8;
    singly.Insert(0, value);

    std::cout << "size: " << singly.Size() << std::endl;
    std::cout << "empty: " << std::boolalpha << singly.Empty() << std::endl;

    std::cout << singly << std::endl;

    return 0;
}
