/**
 * 题目：冒泡排序 -- 交换排序，相邻元素俩俩比较
 * 时间复杂度：O(n²)
 * 空间复杂度：O(1)
 * 稳定性：稳定
 */

#include <iostream>

#include "sort_base.h"


void BubbleSort(List *ls) {
    assert(ls);

    bool sorted = false;  // 性能优化：如果后面子序列已经有序不必循环
    for (int i=0; i<ls->length_ && !sorted; ++i) {
        sorted = true;
        for (int j=ls->length_-2; j>=i; --j) {
            if (ls->data_[j] > ls->data_[j+1]) {
                SwapElem(ls, j, j+1);
                sorted = false;
            }
        }
    }
}

int main() {
    List ls = {{9, 1, 5, 8, 3, 7, 4, 6, 2}, 9};
    BubbleSort(&ls);
    PrintList(&ls);

    return 0;
}
