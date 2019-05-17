/**
 * 题目：归并排序
 * 思想：
 *      归并：在数据结构中的定义是将两个或两个以上的有序表组合成一个新的有序表。
 *      归并排序：就是利用归并的思想。它的原理是假设初始序列含有n个记录，则可以
 *      看成是n个有序的子序列，每个子序列的长度为1，然后两两归并，得到n/2个长度
 *      为2或1的有序子序列；再两两归并，...，如此重复，直至得到一个长度为n的有序
 *      序列为止，这种排序方法称为2路归并排序。其实看起来就是一个倒立的完全二叉
 *      树。这里的两两归并就是就是两个有序的子序列归并成一个有序的序列。
 *      归并排序是一种比较占用内存，但效率高且稳定但排序
 * 时间复杂度：最好、最坏和平均都是O(nlogn)
 * 空间复杂度：
 * 稳定性：稳定排序
 *
 * 改进：对于小规模子序列，可以考虑使用插入排序或选择排序，可以提升性能，消除部
 *       分递归的性能消耗，还可以增加一个判断条件：a[mid] < a[mid+1]，我们就认为
 *       数组已经是有序的并跳过merge
 */

#include <iostream>

#include "sort_base.h"


// 将source[start, mid]和source[mid+1, end]两个有序子序列合并成
// 一个新的有序序列，并存储到target中
void Merge(int *source, int *target, int start, int mid, int end);
// 将source[start ... end]归并排序为target[start ... end]
void MergeSort(int *source, int *target, int start, int end);

void MergeSortEntrance(List *ls) {
    assert(ls);
    MergeSort(ls->data_, ls->data_, 0, ls->length_-1);
}

// 利用递归实现
void MergeSort(int *source, int *target, int start, int end) {
    if (start == end) {  // 最后一个元素
        target[start] = source[start];
        return;
    }
    int temp[MAX_SIZE];  // 需要借助一个临时的数组，性能消耗点
    // 将start ~ end区间一分为二进行归并排序
    int mid = start + ((end-start) >> 1);
    MergeSort(source, temp, start, mid);  // 处理前一半
    MergeSort(source, temp, mid+1, end);  // 处理后一半
    // 对已经排序的两个子序列进行合并，合并成一个新的有序序列
    Merge(temp, target, start, mid, end);
}

void Merge(int *source, int *target, int start, int mid, int end) {
    int first_idx = start;
    int second_idx = mid + 1;
    int target_idx = start;
    for (; first_idx<=mid && second_idx<=end; ) {
        if (source[first_idx] < source[second_idx]) {  // 按照升序排序
            target[target_idx++] = source[first_idx++];
        } else {
            target[target_idx++] = source[second_idx++];
        }
    }
    // 处理剩余的数据
    while (first_idx <= mid) {
        target[target_idx++] = source[first_idx++];
    }
    while (second_idx <= end) {
        target[target_idx++] = source[second_idx++];
    }
}


// 将source中相邻的长度为sub_len的子序列两两归并到target中
void MergePass(int *source, int *target, int sub_len, int len) {
    int i = 0;  // 起始合并位置
    while (i <= (len-2*sub_len)) {
        // 将source合并到target
        Merge(source, target, i, i+sub_len-1, i+2*sub_len-1);  // 两两归并
        i += 2 * sub_len;
    }
    if (i < (len-sub_len)) {  // 还有一个完整的子序列+一个不完整的子序列
        Merge(source, target, i, i+sub_len-1, len-1);
    } else {  // 只剩下一个子序列了（可能完整也可能不完整
        for (int j=i; j<len; ++j) {
            target[j] = source[j];
        }
    }
}

// 使用非递归版本实现归并排序
void MergeSortEntrance2(List *ls) {
    assert(ls);

    // 也需要一个临时的、同等大小的数组-临时缓冲区
    int *target = new int[ls->length_];

    int step = 1;  // 首先将子序列划分为长度为1的有序子序列
    while (step < ls->length_) {
        MergePass(ls->data_, target, step, ls->length_);
        step *= 2;
        MergePass(target, ls->data_, step, ls->length_);
        step *= 2;
    }

    delete[] target;
}

int main() {
    //List ls = {{6, 2, 3, 1, 9, 10, 15, 13, 12, 17}, 10};
    //List ls = {{7, 13, 10, 9, 15, 3, 2, 5, 8, 12, 1, 11, 4, 6, 14}, 15};
    List ls = {{16, 7, 13, 10, 9, 15, 3, 2, 5, 8, 12, 1, 11, 4, 6, 14}, 16};
    MergeSortEntrance2(&ls);
    PrintList(&ls);

    return 0;
}
