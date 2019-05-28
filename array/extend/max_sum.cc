/**
 * 题目：求连续子数组的最大和
 * 描述：输入一个整形数组，数组里有正数也有负数。数组中连续的一个或多个
 *       整数组成一个子数组，每个子数组都有一个和。求所有子数组的和的最
 *       大值。要求时间复杂度为O(n)。
 *       例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，和最大的子数组为3, 
 *       10, -4, 7, 2，因此输出为该子数组的和18。
 */

#include <iostream>

/**
 * 设sum[i]为以第i个元素结尾且和最大的连续子数组。假设对于元素i，所有以它
 * 前面的元素结尾的子数组的长度都已经求得，那么以第i个元素结尾且和最大的
 * 连续子数组实际上，要么是以第i-1个元素结尾且和最大的连续子数组加上这个元
 * 素，要么是只包含第i个元素，即sum[i] = max(sum[i-1] + a[i], a[i])。可以
 * 通过判断sum[i-1] + a[i]是否大于a[i]来做选择，而这实际上等价于判断
 * sum[i-1]是否大于0。由于每次运算只需要前一次的结果，因此并不需要像普通的
 * 动态规划那样保留之前所有的计算结果，只需要保留上一次的即可，因此算法的
 * 时间和空间复杂度都很小。
 */
bool g_invalid_input = false;

int FindMaxSumOfSubArray(int *nums, int len) {
    g_invalid_input = false;
    if (!nums || len<=0) {
        g_invalid_input = true;
        return 0;
    }    

    int max_sum = 0x80000000;
    int cur_sum = 0;
    for (int idx=0; idx<len; ++idx) {
        if (cur_sum <= 0) {
            cur_sum = nums[idx];
        } else {
            cur_sum += nums[idx];
        }
        if (cur_sum > max_sum) {
            max_sum = cur_sum;
        }
    }

    return max_sum;
}

int main() {
    return 0;
}
