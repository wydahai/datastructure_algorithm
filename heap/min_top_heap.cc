#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

template<typename T>
void Print(const std::vector<T> &arrs) {
    std::for_each(arrs.cbegin(), arrs.cend(), 
                  [](const T &elem) { std::cout << elem << ' '; });
    std::cout << std::endl;
}

template<typename T>
void AdjustUpward(std::vector<T> &arrs, 
                  size_t parent, 
                  size_t size=0) {
    assert(parent<arrs.size() && size<=arrs.size());

    size_t adjustSize = size==0?arrs.size():size;
    T parentValue = arrs[parent];
    size_t child = 2 * parent + 1;  // left child index
    while (child < adjustSize) {
        // get the minimum value from the childs
        if ((child+1)<adjustSize && arrs[child+1]<arrs[child]) {
            ++child;
        }
        if (parentValue > arrs[child]) {
            arrs[parent] = arrs[child];
            parent = child;
            child = 2 * parent + 1;
        } else {
            break;  // no need to adjust
        }
    }
    arrs[parent] = parentValue;
}

template<typename T>
void BuildMinTopHeap(std::vector<T> &arrs) {
    for (ssize_t idx=(arrs.size()/2-1); idx>=0; --idx) {
        AdjustUpward(arrs, idx);
    }
}

// 按照降序进行排序
template<typename T>
void SortHeap(std::vector<T> &minTopHeap) {
    /**
     * 注意：不能写成idx>=0，最后一个不需要排序，且
     * AdjustUpward的实现逻辑会有问题
     */
    for (ssize_t idx=minTopHeap.size()-1; idx>0; --idx) {
        std::swap(minTopHeap[0], minTopHeap[idx]);
        /**
         * 因为交换的是首尾元素，且交换后的尾元素已经满足排序
         * 条件（当前堆中最小的元素），所以需要每次对首尾元素
         * 进行调整，以达到满足小顶堆的条件
         */
        AdjustUpward(minTopHeap, 0, idx);
    }
}

int main(int argc, char *argv[]) {
    std::vector<int> arrs = {23, 65, 12, 3, 8, 76, 
        345, 90, 21, 75, 34, 61};
    std::cout << "origin arrays:" << std::endl;
    Print(arrs);

    BuildMinTopHeap(arrs);
    std::cout << "init a min top heap:" << std::endl;
    // output: 3 8 12 21 23 61 345 90 65 75 34 76 
    Print(arrs);

    SortHeap(arrs);
    std::cout << "after decending sort:" << std::endl;
    // output: 345 90 76 75 65 61 34 23 21 12 8 3
    Print(arrs);

    return 0;
}
