/**
 * 题目：插值查找
 * 插值公式：mid = low + (high-low) * (key-a[low]) / (a[high]-a[low])
 * 时间复杂度：O(logn)
 * 适用场景：表长比较大，而关键字分布比较均匀的查找表比较适合，平均性能
 *           要好于折半查找
 */

#include <iostream>


int InterpolationSearch(int nums[], int len, int key) {
    if (!nums || len<=0) {
        return -1;
    }

    int low = 0;
    int high = len;
    int mid;
    while (low <= high) {
        mid = low + (high-low)*(key-nums[low])/(nums[high]-nums[low]);
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
    int idx = InterpolationSearch(nums, len, key);
    std::cout << "idx = " << idx << std::endl;

    key = 10;
    idx = InterpolationSearch(nums, len, key);
    std::cout << "idx = " << idx << std::endl;

    return 0;
}
