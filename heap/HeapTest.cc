#include <iostream>
#include <vector>

#include "MinBinaryHeap.h"


static
void MinBinaryHeapTest() {
    auto heap = MinBinaryHeap<int>();
    std::cout << "Empty Heap: " << heap << std::endl;

    std::vector<int> arrays = {23, 65, 12, 3, 8, 76, 345, 90, 21, 75, 34, 61};
#if 0
    // 调用move版本的insert
    for (auto &value : arrays) {
        heap.Insert(std::move(value));
    }
    // 当传递字面值常量时优先调用右值引用版本，若不存在则调用const引用版本
    heap.Insert(0);
#else
    for (const auto &value : arrays) {
        heap.Insert(value);
    }
#endif
    std::cout << heap << std::endl;
    std::cout << "size: " << heap.Size() << std::endl;
    std::cout << "Min: " << heap.Min() << std::endl;

    while (heap.Size() > 0) {
        std::cout << "deleted value: " << heap.Delete() << std::endl;
        std::cout << heap << std::endl;
    }
    std::cout << "heap size: " << heap.Size() << std::endl;

    for (const auto &value : arrays) {
        heap.Insert(value);
    }
    std::cout << "origin: " << heap << std::endl;
    heap.SortByDesc();
    std::cout << "after sort(desc): " << heap << std::endl;
    // heap.SortByAsc();
    // std::cout << "after sort(asc): " << heap << std::endl;



    Array<int> arrays2{12};
    size_t idx = 0;
    for (const auto &value : arrays) {
        arrays2[idx++] = value;
    }
    MinBinaryHeap<int> heap2{arrays2};
    std::cout << heap2 << std::endl;

}

int main() {
    MinBinaryHeapTest();

    return 0;
}
