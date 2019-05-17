/**
 * 题目：斐波那契查找 - 利用黄金分割的原理
 * 原理：就是利用其计算原理来进行分割：F(k) = F(k-1) + F(k-2)
 * 时间复杂度：O(logn)
 * 适用场景：如果要查找的key在序列的右侧，那么左侧的子序列不需要查找，
 *           此时对于处理大部分数据，平均性能要好于折半查找，但是若要
 *           是一直在左侧序列进行查找，则性能会低于折半查找，另外它使
 *           用加法操作来计算mid；插值查找使用四则运算；折半查找使用
 *           除法运算（实际可以转换为移位提供性能）
 * 说明：n=F(k)-1， 表中记录的个数为某个斐波那契数小1，原因：
 *       是为了格式上的统一，方便递归或者循环程序的编写。表中的数据是
 *       F(k)-1个，使用mid值进行分割又用掉一个，那么剩下F(k)-2个。正好
 *       分给两个子序列，每个子序列的个数分别是F(k-1)-1与F(k-2)-1个，
 *       格式上与之前是统一的。不然的话，每个子序列的元素个数有可能是
 *       F(k-1)，F(k-1)-1，F(k-2)，F(k-2)-1个，写程序会非常麻烦。
 */

#include <iostream>


// 构建斐波那契数列
long Fabonacci(unsigned num) {
    static int result[] = {0, 1};
    if (num < 2) {
        return result[num];
    }

    long fib_minus_one = result[1];
    long fib_minus_two = result[0];
    long fib_num = 0;
    for (unsigned idx=2; idx<=num; ++idx) {
        fib_num = fib_minus_one + fib_minus_two;
        fib_minus_two = fib_minus_one;
        fib_minus_one = fib_num;
    }
    return fib_num;
}


int FabonacciSearch(int nums[], int len, int key) {
    if (!nums || len<=0) {
        return -1;
    }

    // 要求待查找的数组的长度n = Fabonacci(k) - 1，所以要首先确定k值
    int k = 0;
    while (len > Fabonacci(k)-1) {  // 找到len最接近的Fabonacci
        ++k;
    }
    // 因为实际的len可能小于Fabonacci(k)-1，所以需要使用nums最后一个
    // 元素进行填充
    // 为了提升性能，可以将计算出的Fabonacci(k)-1缓存下来
    for (int idx=len; idx<Fabonacci(k)-1; ++idx) {
        nums[idx] = nums[len-1];
    }
    // 上面两步直白的说就是将待排序序列扩充，使其元素的个数为Fabonacci(k)-1，
    // 这样就可以利用Fabonacci进行分割了

    int low = 0;
    int high = len - 1;
    int mid;
    while (low <= high) {
        // 通过k的fabonacci分割成左右两侧，在记录的右侧进行查找
        mid = low + Fabonacci(k-1) - 1;
        if (key < nums[mid]) {  // 需要在左侧查找
            high = mid - 1;
            k -= 1;
        } else if (key > nums[mid]) {  // 需要在右侧内查找
            low = mid + 1;
            k -= 2;
        } else {
            // 需要判断找到的位置是不是填充的部分
            return mid<len?mid:len-1;
        }
    }
    return -1;
}

int main() {
    int nums[64] = {-32, 12, 16, 24, 36, 45, 59, 98};
    size_t len = 8;

    int key = 12;
    int idx = FabonacciSearch(nums, len, key);
    std::cout << "idx = " << idx << std::endl;

    key = 10;
    idx = FabonacciSearch(nums, len, key);
    std::cout << "idx = " << idx << std::endl;

    return 0;
}
