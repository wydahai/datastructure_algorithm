/**
 * 题目：合并两个有序的数组
 * 描述：有两个排序的数组A和B，假设A有足够的剩余空间容纳B。请实现一个函数
 *       将B中的元素插入到A中，并且插入后所有的元素仍然是有序的
 * 解答：从后向前移动，这样可以减少移动次数，来提供性能
 */
#include <iostream>


void MergeOrederdArray(int *first, int first_len, 
                       int *second, int second_len) {
    if (!first || first_len<=0) {  // 不满足要求
        return;
    }
    if (!second || second_len<=0) {  // 不需要合并
        return;
    }

    int new_idx = first_len + second_len - 1;
    int first_idx = first_len - 1;
    int second_idx = second_len - 1;
    while (first_idx>=0 && second_idx>=0) {
        if (first[first_idx] <= second[second_idx]) {
            first[new_idx--] = second[second_idx--];
        } else {
            first[new_idx--] = first[first_idx--];
        }
    }
    //if (first_idx  > 0) {  // 是否有必要
    //    while (first_idx >= 0) {
    //        first[new_idx--] = first[first_idx--];
    //    }
    //}
    if (second_idx > 0) {
        while (second_idx >= 0) {
            first[new_idx--] = second[second_idx--];
        }
    }
} 


int main() {
    int first[16] = {0, 1, 2, 4, 5, 7, 9};
    int second[16] = {2, 3, 6, 8, 10};
    //MergeOrederdArray(first, 7, second, 5);
    //for (int idx=0; idx<11; ++idx) {
    //    std::cout << first[idx] << ' ';
    //}
    //std::cout << std::endl;
    MergeOrederdArray(second, 5, first, 7);
    for (int idx=0; idx<12; ++idx) {
        std::cout << second[idx] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
