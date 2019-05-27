/**
 * 题目：调整数组顺序使奇数位于偶数前面
 * 描述：输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位
 *       于数组的前半部分，所有偶数位于数组的后半部分。
 * 分析：可以维护两个指针i和j，i指向数组的第一个数字，它只向后移动；j指向数组的最
 *       后一个数字，它只向前移动。在两个指针相遇之前，第一个指针总是位于第二个指
 *       针的前面。如果第一个指针指向的数字为偶数，并且第二个指针指向的数字是奇数，
 *       就交换这两个数字。当两个指针相遇时，表示所有的奇数都已经在偶数的前面了。
 */

#include <iostream>
#include <algorithm>

void ReorderOddEven(int *nums, unsigned len) {
    if (!nums || len<=1) {
        return;
    }

    int *lhs = nums;
    int *rhs = nums + len - 1;
    while (lhs < rhs) {
        // 判断条件可以通过函数指针的方式进行传递，这样可以提供可扩展性
        while (lhs<rhs && *lhs & 0x01) {  // 从左侧找到第一个不为奇数的整数
            ++lhs;
        }
        while (rhs>lhs && !(*rhs & 0x01)) {
            --rhs;
        }
        if (lhs < rhs) {  // 交换两个位置的数字
            *lhs ^= *rhs;
            *rhs ^= *lhs;
            *lhs ^= *rhs;
        }
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    ReorderOddEven(nums, sizeof(nums)/sizeof(nums[0]));
    for (auto it=std::begin(nums); it!=std::end(nums); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    return 0;
}
