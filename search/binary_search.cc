/**
 * 题目：二分查找（折半查找）
 * 要求：要使用二分查找，则待查找序列必须有序，且是连续存储
 * 时间复杂度：O(logn)
 * 场景：折半查找的前提条件是有序表顺序存储，对于静态查找表，一次排序后不再
 *       变化，比较适合这种情况。但对于需要频繁插入、删除操作的数据集来说，
 *       维护有序的排序会带来不小的工作量和消耗，所以不适合。
 */

#include <iostream>


int BinarySearch(int nums[], int len, int key) {
    if (!nums || len<=0) {
        return -1;
    }

    int low = 0;
    int high = len - 1;
    int mid = 0;
    while (low <= high) {
        mid = low + ((high-low) >> 1);  // 性能比除法要好
        if (key < nums[mid]) {
            high = mid - 1;
        } else if (key > nums[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }

    return -1;
}

int main() {
    int nums[] = {-32, 12, 16, 24, 36, 45, 59, 98};
    size_t len = sizeof(nums)/sizeof(nums[0]);

    int key = 12;
    int idx = BinarySearch(nums, len, key);
    std::cout << "idx = " << idx << std::endl;

    key = 10;
    idx = BinarySearch(nums, len, key);
    std::cout << "idx = " << idx << std::endl;

    return 0;
}
