/**
 * 题目：数组中只出现一次的数字
 */

#include <iostream>
#include <cassert>

/**
 * 描述：一个数组中有一个数字出现了一次，其余的数字都出现了两次。
 *       快速找出只出现一次的那个数字。
 * 分析：
 *       第一种方法：使用hash table存储每个数字出现的次数
 *       第二种方法：利用异或运算：相同的数字异或为0
 */
int FindOnlyOneNum(int nums[], int len) {
    assert(nums && len>=1);
    int ret = 0;  // 任何数字与0异或的结果还是它本身
    // 循环遍历时相同的数字会被抵消掉
    for (int idx=0; idx<len; ++idx) {
        ret ^= nums[idx];
    }
    return ret;
}

/**
 * 描述：一个整型数组里除了两个数字之外，其他的数字都出现了两次。
 *       请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，
 *       空间复杂度是O(1)。
 * 分析：
 *       利用一个数组中有一个数字只出现了一次的思想，使用异或，将
 *       此数组拆分成两个子数组，每个子数组中只包含一个只出现一次
 *       的数字，现在转换为了求出每个子数组中出现一次的数字，如何
 *       分隔成两个子数组？对原数组遍历进行异或运算的结果固定不为
 *       0（因为有两个不相同的数字），则说明该异或结果的第n位是1，
 *       这样通过判断原数组中第n位是不是1来将其划分为两个子数组，
 *       因为相同的数字第n位一定是一样的，那两个不同的数字的第n位
 *       固定是不一样的，会被分配到不同的两个子数组中。
 */
unsigned FindFirstBitIs1(int num);
bool IsBit1(int num, unsigned idx);
void FindNumsAppearOnce(int nums[], int len, 
                        int *first, int *second) {
    assert(nums && len>=2);

    // 首先遍历数组中的数字，得到异或的结果
    int result_exclusive_or = 0;
    for (int idx=0; idx<len; ++idx) {
        result_exclusive_or ^= nums[idx];
    }

    // 获取从右边开始第一个位为1的位置：n
    unsigned first_index_of_1 = FindFirstBitIs1(result_exclusive_or);
    
    // 通过位置n将原数组划分为两个子数组，并分别计算
    *first = 0;
    *second = 0;
    for (int idx=0; idx<len; ++idx) {
        if (IsBit1(nums[idx], first_index_of_1)) {
            *first ^= nums[idx];
        } else {
            *second ^= nums[idx];
        }
    }
}

unsigned FindFirstBitIs1(int num) {
    // 通过移位运算来实现，转换为最后一位是否为1
    unsigned index_bit = 0;
    while ((num&0x1)==0 && (index_bit<8*sizeof(int))) {
        num >>= 1;
        ++index_bit;
    }
    return index_bit;
}

// 判断数字num的第idx位是否为1
bool IsBit1(int num, unsigned idx) {
    num >>= idx;
    return num & 0x1;
}

int main() {
    int nums[] = {1, 2, 3, 3, 2, 4, 1};
    std::cout << FindOnlyOneNum(nums, sizeof(nums)/sizeof(nums[0])) 
        << std::endl;

    int nums1[] = {1, 1, 2, 2, 3, 3, 8, 9};
    int first = 0;
    int second = 0;
    FindNumsAppearOnce(nums1, sizeof(nums1)/sizeof(nums1[0]), 
                       &first, &second);
    std::cout << first << ' ' << second << std::endl;

    return 0;
}
