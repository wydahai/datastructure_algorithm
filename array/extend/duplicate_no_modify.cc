/**
 * 题目：不修改数组找出重复数字
 * 描述：在一个长度为n+1的数组里所有数字都在1~n的范围内，所有数组中至少
 *       有一个数字是重复的。请找出数组中任意一个重复的数字，但不能修改
 *       输入的数组。
 * 解答：
 *       第一种方法：再创建一个数组，将输入数组的内容拷贝到新数组中，然
 *       后采用duplicate.cc中的方法，但是空间复杂度是O(n)
 *       第二种方法：分析，n+1长度，数字范围是1～n，所以一定有重复的
 *       利用二分查找的方式：我们将1~n从中间分成两份，1~m和m+1~n，遍历数
 *       组分别统计数组中出现1~m的元素的个数和出现m+1~n的个数，对于统计
 *       个数大于对应的长度时，则说明该份中出现了重复元素；
 *       对出现重复元素的一份继续进行折半划分，一直到单份长度为1，但统计
 *       却含有多个元素的情况，则找到重复元素；
 *       这种方法无法保证找出所有的重复数字，需要在解决前了解需求。
 *       这种方法不能保证找出所有重复的数字，例如不能找出{2, 3, 5, 4, 3, 
 *       2, 6, 7}中的数字2，因为1 ～ 2是两个数字，这个范围内2出现了两次，
 *       需要在题目中再加上一个限定条件：保证数组中会出现范围1~n的每一个
 *       数字
 */
#include <iostream>


int RangeCount(const int nums[], int length, int start, int end);


int Duplicate(const int nums[], int length) {
    if (!nums || length <= 0) {
        return -1;
    }

    // nums中数字的范围：1 ~ length-1
    int start = 1;
    int end = length - 1;
    while (start <= end) {
        int mid = start + ((end-start) >> 1);  // 取start和end中间的数字
        // 因为题目中说明一定会存在重复的数字，所以值需要判断start ~ mid
        // 中间是否有重复即可，若没有重复则会在mid+1 ~ end之间
        // 计算nums中所有的元素在数字start ~ end之间出现的次数
        int count = RangeCount(nums, length, start, mid);
        if (start == end) {  // 最后一个元素了
            if (count > 1) {  // 说明该元素是重复的
                return start;
            } else {
                break;  // 没有重复的元素，应该是异常情况
            }
        }
        // nums所有元素在此区间出现的次数与数字区间mid-start+1应有的元素
        // 个数相等，则说明此区间没有重复的数字
        if (count > (mid-start+1)) {
            end = mid;
        } else {
            start = mid + 1;
        }
    }

    return -1;
}


// 遍历nums中的所有元素，统计nums中的元素在start ~ end区间出现
// 的次数，如果出现的次数大于end - start + 1个数，则说明一定有
// 重复的数字在该区间
int RangeCount(const int nums[], int length, int start, int end) {
    if (!nums || length<0) {
        return 0;
    }

    int count = 0;
    for (int idx=0; idx<length; ++idx) {
        if (nums[idx]>=start && nums[idx]<=end) {
            ++count;
        }
    }
    return count;
}


int main() {
    int nums[] = {2, 3, 1, 0, 2, 5, 3};
    int length = sizeof(nums)/sizeof(nums[0]);
    int idx = Duplicate(nums, length);
    std::cout << "idx = " << idx << std::endl;
    if (idx == -1) {
        std::cout << "no duplicated number" << std::endl;
    } else {
        std::cout << "duplicated number: " << nums[idx] << std::endl;
    }

    return 0;
}
