/**
 * 题目：数组中出现次数超过一半的数字
 * 描述：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
 *       比如输入一个长度为9的数组{1, 2, 3, 2, 2, 2, 5, 4, 2}, 因为数组
 *       中数字2出现了5次，超过数组的长度的一半，因此输出2
 */

#include <iostream>

bool g_invalid_params = false;

bool CheckParams(int *nums, int len) {
    g_invalid_params = false;
    if (!nums || len<=0) {
        g_invalid_params = true;
    }
    return g_invalid_params;
}

int Partition(int *nums, int start, int end) {
    int pivot = nums[start];
    while (start < end) {
        while (end>start && nums[end]>=pivot) {
            --end;
        }
        nums[start] = nums[end];
        while (start<end && nums[start]<=pivot) {
            ++start;
        }
        nums[end] = nums[start];
    }
    nums[start] = pivot;
    return start;
}

bool CheckMoreThanHalf(int *nums, int len, int num) {
    int times = 0;
    for (int idx=0; idx<len; ++idx) {
        if (nums[idx] == num) {
            ++times;
        }
    }
    bool more_than_half = true;
    if (times*2 <= len) {
        more_than_half = false;
        g_invalid_params = true;
    }
    return more_than_half;
}

// 第一种方法：利用快速排序的Patition来进行查找
// 出现次数超过数组的一半，则说明一定会出现在中间位置，
// 通过排序获取到中间位置数据即可
int MoreThanHalfNum_V1(int *nums, int len) {
    if (CheckParams(nums, len)) {
        return 0;
    }

    int middle = len >> 1;
    int start = 0;
    int end = len - 1;
    int index = Partition(nums, start, end);
    while (index != middle) {
        if (index > middle) {
            end = index - 1;
            index = Partition(nums, start, end);
        } else {
            start = index + 1;
            index = Partition(nums, start, end);
        }
    }
    int result = nums[middle];
    if (!CheckMoreThanHalf(nums, len, result)) {
        result = 0;
    }
    return result;
}

// 数字次数超过一半，则说明：该数字出现的次数比其他数字之和还多
// 遍历数组过程中保存两个值：一个是数组中某一数字，另一个是次数。
// 遍历到下一个数字时，若与保存数字相同，则次数加1，反之减1。若
// 次数=0，则保存下一个数字，次数重新设置为1。由于要找的数字出现
// 的次数比其他数字之和还多，那么要找的数字肯定是最后一次把次数
// 设置为1的数字。
int MoreThanHalfNum_V2(int *nums, int len) {
    if (CheckParams(nums, len)) {
        return 0;
    }

    int result = nums[0];
    int times = 1;
    for (int idx=1; idx<len; ++idx) {
        if (times == 0) {
            result = nums[idx];
            times = 1;
        } else if (nums[idx] == result) {
            ++times;
        } else {
            --times;
        }
    }

    if (!CheckMoreThanHalf(nums, len, result)) {
        result = 0;
    }
    return result;
}

int main() {
    int nums[] = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    std::cout << MoreThanHalfNum_V1(nums, sizeof(nums)/sizeof(nums[0])) 
        << std::endl;
    int nums1[] = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    std::cout << MoreThanHalfNum_V1(nums1, sizeof(nums1)/sizeof(nums1[0])) 
        << std::endl;

    return 0;
}
