/**
 * 题目：最长上升子序列问题（Longest Increasing Subsequence）LIS
 * 描述：指在一个序列中求长度最长的一个上升子序列的问题，是动态规划中一个
 *       相当经典问题。如1,5,3,4,6,9,7,8的LIS为1,3,4,6,7,8，长度为6。
 * 分析：这个上升实质上就是一个对<进行定义的过程，所以我们求解的其实是一
 *       类问题，也就是在给定序列中求解长度最长的符合某一性质的子序列的问
 *       题。
 *       例如：给定一个长度为1000以内的数组，每个元素范围都在[0,10000]的整
 *       数，求这个数组的LIS。
 *
 * 动态规划解法：
 *       状态定义：LIS(i)表示以第i个数字结尾的最长上升子序列的长度
 *                 LIS(i)表示[0...i]范围内，选择数字nums[i]可以获得的最长上
 *                 升子序列的长度
 *       状态转移：LIS[i] = max(1+LIS[j] if nums[i]>nums[j])(j<i)
 */

#include <iostream>
#include <algorithm>

// sub_lens[i]表示以i结尾的子序列中LIS的长度，sub_lens[j](0<=j<i)表示i之前
// 的LIS长度（最大长度），可以看到：只有当nums[j] < nums[i]的时候才需要判断
// 是否将nums[j]加入到nums[i]中，需要判断加入nums[j]后与不加入时哪个最大，
// 选择最大的一个：sub_lens[i] = max(sub_lens[i], sub_lens[j]+1)（sub_lens
// [j]表示以j结尾的长度，+1表示要把此值也要计算进去）
int MaxLIS(int nums[], int len) {
    if (!nums || len==0) {
        return 0;
    }

    int *sub_lens = new int[len];  // 存储第i个数字结尾时的最大长度
    for (int idx=0; idx<len; ++idx) {
        sub_lens[idx] = 1;
    }
    for (int i=0; i<len; ++i) {  // 计算所有以idx处的数字结尾的长度
        // 下面的循环实现的是寻找0-i之间的以i结尾的最长上升子序列，
        // 寻找这个最大值
        for (int j=0; j<i; ++j) {
            if (nums[j] < nums[i]) {
                // 因为j永远小于i，所以sub_lens[j]的值在之前的计算过程中
                // 已经算出
                sub_lens[i] = std::max(sub_lens[i], sub_lens[j]+1);
            }
        }
    }

    int max_len = 0;
    for (int idx=0; idx<len; ++idx) {
        if (max_len < sub_lens[idx]) {
            max_len = sub_lens[idx];
        }
    }
    delete[] sub_lens;
    return max_len;
}


// 在上面的方法中，花费了挺大的时间用于查找最大的sub_lens[j]（第二个循环做的
// 事情），如果有办法让sub_lens[j]变成一个递增的序列，就能够使用二分来进行优
// 化，从而使时间复杂度有O(n*n)降低到O(nlogn)，方法是有的：可以用sub_lens[i]
// 来保存在前i个数中最大的那个数，这样sub_lens[i]中存储的数据就是递增的了，
// 对于每一个sub_lens[i]，我们都在sub_lens数组中寻找比它大的第一个数的下标，
// 假设为pos，然后利用sub_lens[i]来更新sub_lens[pos]，所以max_len应该就是max
// (max_len, pos+1)
int MaxLISV2(int nums[], int len) {
    if (!nums || len<=0) {
        return 0;
    }

    int *sub_lens = new int[len];
    for (int idx=0; idx!=len; ++idx) {
        sub_lens[idx] = 0;
    }

    int max_len = 1;  // 只要有数据，则长度一定会大于等于1
    sub_lens[0] = nums[0];  // 初始化时最大值应该时第一个元素
    for (int idx=1; idx<len; ++idx) {
        // std::lower_bound返回区间[sub_lens, sub_lens+max_len)内第一个大于等
        // 于nums[idx]的值
        int pos = (std::lower_bound(sub_lens, sub_lens+max_len, nums[idx]) - 
                   sub_lens);
        std::cout << "pos = " << pos << std::endl;
        sub_lens[pos] = nums[idx];
        max_len = std::max(max_len, pos+1);
        for (int idx=0; idx<len; ++idx) {
            std::cout << sub_lens[idx] << ' ';
        }
        std::cout << std::endl;
    }

    for (int idx=0; idx<len; ++idx) {
        std::cout << sub_lens[idx] << ' ';
    }
    std::cout << std::endl;
    delete[] sub_lens;
    return max_len;
}

int main() {
    int nums[] = {1, 5, 3, 4, 6, 9, 7, 8};
    std::cout << MaxLIS(nums, sizeof(nums)/sizeof(nums[0])) << std::endl;
    std::cout << MaxLISV2(nums, sizeof(nums)/sizeof(nums[0])) << std::endl;

    return 0;
}
