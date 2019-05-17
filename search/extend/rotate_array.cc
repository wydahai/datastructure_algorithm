/**
 * 题目：旋转数组的最小数字
 * 描述：把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
 *       输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。例如数组
 *       {3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1
 * 分析：二分查找，两个指针分别指向第一个和最后一个，那么第一个应该是大于
 *       或等于第二个（特例：旋转数组就是旋转前本身），最小的元素刚好把该
 *       数组划分为两个有序的子数组（其实最大元素也是这样）
 * 解答：利用二分查找思想，这样的序列其实是由两个有序（递增）的子序列组成，
 *       利用二分查找思想，通过确定mid_index是隶属于哪个子序列来确定范围，
 *       若nums[lhs_index] <= nums[mid_index]，说明mid_index在左侧（递增）
 *       子序列；
 *       若nums[mid_index] <= nums[rhs_index]，说明mid_index在右侧（递增）
 *       子序列
 * 时间复杂度：O(logn)
 */

#include <iostream>
#include <exception>

// 顺序查找最小的元素
int MinInOrder(int nums[], int start, int end) {
    int min_num = nums[start];
    while (start <= end) {
        if (min_num < nums[start]) {
            min_num = nums[start];
        }
        ++start;
    }
    return min_num;
}

int MinNum(int nums[], int len) {
    if (!nums || len<=0) {
        throw("Invalid input");
    }

    // 找到后lhs_index指向的是最大的元素，rhs_index指向的是最小的元素
    int lhs_index = 0;
    int rhs_index = len - 1;
    int mid_index = lhs_index;  // 假设旋转数组就是原递增数组，此时需要支持
    while (nums[lhs_index] >= nums[rhs_index]) {
        if (rhs_index-lhs_index == 1) {  // 已找到
            mid_index = rhs_index;
            break;
        }
        mid_index = lhs_index + ((rhs_index-lhs_index)>>1);
        // 如果最左侧、中间和最右侧的值相等，此时只能通过顺序查找
        // 如{0, 1, 1, 1, 1}的两个旋转{1, 0, 1, 1, 1}和{1, 1, 1, 0, 1}，无法
        // 确定中间位置的1是属于第一个递增子序列还是第二个递增子序列
        if (nums[lhs_index]==nums[mid_index] && 
            nums[mid_index]==nums[rhs_index]) {
            mid_index = MinInOrder(nums, lhs_index, rhs_index);
            break;
        }

        if (nums[lhs_index] <= nums[mid_index]) {  // mid_index在左侧
            lhs_index = mid_index;
        } else if (nums[rhs_index] >= nums[mid_index]){  // mid_index在右侧
            rhs_index = mid_index;
        }
    }
    return nums[mid_index];
}

int main() {
    int first[] = {3, 4, 5, 1, 2};
    int len = sizeof(first) / sizeof(first[0]);
    std::cout << MinNum(first, len) << std::endl;

    int second[] = { 3, 4, 5, 1, 1, 2 };
    len = sizeof(second) / sizeof(second[0]);
    std::cout << MinNum(second, len) << std::endl;

    int third[] = { 3, 4, 5, 1, 2, 2 };
    len = sizeof(third) / sizeof(third[0]);
    std::cout << MinNum(third, len) << std::endl;

    int forth[] = { 1, 0, 1, 1, 1 };
    len = sizeof(forth) / sizeof(forth[0]);
    std::cout << MinNum(forth, len) << std::endl;

    int fifth[] = { 1, 2, 3, 4, 5 };
    len = sizeof(fifth) / sizeof(fifth[0]);
    std::cout << MinNum(fifth, len) << std::endl;

    return 0;
}
