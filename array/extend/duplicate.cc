/**
 * 题目：找出数组中的重复数字
 * 描述：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字
 *       是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。
 *       请找出数组中任意一个重复的数字。
 * 解答：
 *       第一种方法：对数组进行排序然后再进行判断，时间复杂度O(nlogn)
 *       第二种方法：利用hash table，进行统计，时间复杂度O(n)，但是空间复杂
 *                   度也是O(n)
 *       第三种方法：因为数字范围是0 - n-1，所以如果没有重复的则排序后下标
 *                   位置对应的元素值刚好是下标，如果有重复的，则会占用多余
 *                   的位置，描述：假设下标索引为i，该索引对应的值为v，当扫
 *                   描到i时，判断i是否和v相等：若相等则继续扫描下一个元素；
 *                   若不相等，则和下标为v的元素进行比较是否相等，若相等则该
 *                   元素是一个重复的；若不相等则与下标为v的元素进行交换，继
 *                   续判断下标i的元素值是否与该元素值作为下标的元素相等，不
 *                   相等则继续交换，然后重复；若相等，则判断下一个元素，时
 *                   间复杂度O(n)，空间复杂度O(1)
 */
#include <iostream>



void Print(const int nums[], int length) {
    for (int idx=0; idx<length; ++idx) {
        std::cout << nums[idx] << ' ';
    }
    std::cout << std::endl;
}

// NOTE：因为会修改nums，所以此处不能是const
bool Duplicate(int nums[], int length, int *dup_num) {
    if (!nums || length < 1) {
        return false;
    }

    // 检查所有的元素是否都在0 ~ n-1的范围内
    for (int idx=0; idx<length; ++idx) {
        if (nums[idx]<0 || nums[idx]>length-1) {
            return false;
        }
    }

    for (int idx=0; idx<length; ++idx) {
        while (idx != nums[idx]) {  // 若当前下标与其元素值不相等
            // 判断该元素值是否与以该元素值作为下标的元素值相等
            if (nums[idx] == nums[nums[idx]]) {  // 相等则重复
                *dup_num = nums[idx];
                return true;
            } else {  // 否则交换元素：将当前元素交换到对应的下标位置，
                      // 然后继续检查交换后的值是否与当前下标相等
                nums[idx] ^= nums[nums[idx]];
                nums[nums[idx]] ^= nums[idx];
                nums[idx] ^= nums[nums[idx]];
            }
            Print(nums, length);
        }
        // 若当前下标与其元素值相等则判断下一个元素
    }
    return false;
}


int main() {
    int nums[] = {2, 3, 1, 0, 2, 5, 3};
    int length = sizeof(nums)/sizeof(nums[0]);
    int dup_num = -1;
    bool duplicated = Duplicate(nums, length, &dup_num);
    std::cout << "duplicated: " << std::boolalpha << duplicated 
        << ", dup_num: " << dup_num << std::endl;
    Print(nums, length);


    return 0;
}
