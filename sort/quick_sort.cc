/**
 * 题目：快速排序 - 交换排序
 * 思想：通过一趟排序将待排记录分割成独立的两部分，其中一部分记录的关键字
 *       小于（大于）另外一部分记录的关键字，则可分别对这两部分记录继续进
 *       行排序，从而达到整个序列的有序的目的。
 *       也是一种交换排序，也要通过不断的比较和交换来达到排序的目的，但是
 *       它增大来比较和移动的距离，将关键字大的记录直接移动到后面，将关键
 *       字小的记录直接移动到前面（升序），从而减少来总的比较和移动交换次
 *       数。
 * 时间复杂度：O(nlogn)
 * 空间复杂度：O(logn)
 * 稳定性：非稳定
 */

#include <iostream>

#include "sort_base.h"


// 分区：将ls中关键字大的记录移动到右侧，关键字小的记录移动到左侧（升序）
// 返回比较的结束位置
int Partition(List *ls, int low, int high) {
    int base = ls->data_[low];  // 选择一个基准值
    while (low < high) {
        // 先从右至左的顺序扫描，直至遇到第一个比base小的记录
        while (high>low && ls->data_[high]>=base) {
            --high;
        }
        SwapElem(ls, low, high);
        while (low<high && ls->data_[low]<=base) {
            ++low;
        }
        SwapElem(ls, low, high);
    }
    ls->data_[low] = base;
    return low;  // 返回中枢位置
}

// 将数列中的中间数放到序列的位置
void SwapNums(List *ls, int low, int high) {
    int mid = low + ((high-low)>>1);
    if (ls->data_[low] > ls->data_[high]) {  // 将low和high中最小值放入到low
        SwapElem(ls, low, high);
    }
    if (ls->data_[mid] > ls->data_[high]) {  // 保证mid最小
        SwapElem(ls, mid, high);
    }
    if (ls->data_[mid] > ls->data_[low]) {  // 保证low最小
        SwapElem(ls, low, mid);
    }
}

// 优化后的函数
int PartitionOpt(List *ls, int low, int high) {
    // 优化1:对于基准值通过三数取中法：low mid high
    SwapNums(ls, low, high);  // 经过交换后：最左端值在三者间最小，中间数为中，最右端最大
    int base = ls->data_[low];  // 选择一个基准值
    while (low < high) {
        // 先从右至左的顺序扫描，直至遇到第一个比base小的记录
        while (high>low && ls->data_[high]>=base) {
            --high;
        }
        // 优化2.去掉交换，直接赋值
        // SwapElem(ls, low, high);
        ls->data_[low] = ls->data_[high];
        while (low<high && ls->data_[low]<=base) {
            ++low;
        }
        // SwapElem(ls, low, high);
        ls->data_[high] = ls->data_[low];
    }
    ls->data_[low] = base;
    return low;  // 返回中枢位置
}

// 递归实现
void QuickSort(List *ls, int low, int high) {
    // 优化3.此处可以增加一个判断，当high-low的范围比较小时，直接使用插入排序
    if (low < high) {
        int pivot = PartitionOpt(ls, low, high);  // 将ls一分为二
        QuickSort(ls, low, pivot-1);
        QuickSort(ls, pivot+1, high);
    }
}


// 优化4：使用尾递归
void QuickSort1(List *ls, int low, int high) {
    while (low < high) {
        int pivot = PartitionOpt(ls, low, high);
        QuickSort1(ls, low, pivot-1);
        low = pivot + 1;  // 尾递归
    }
}

void QuickSortEntrance(List *ls) {
    assert(ls);
    // QuickSort(ls, 0, ls->length_-1);
    QuickSort1(ls, 0, ls->length_-1);
}

int main() {
    // List ls = {{50, 10, 90, 30, 70, 40, 80, 60, 20}, 9};
    List ls = {{16, 7, 13, 10, 9, 15, 3, 2, 5, 8, 12, 1, 11, 4, 6, 14}, 16};
    QuickSortEntrance(&ls);
    PrintList(&ls);

    return 0;
}
