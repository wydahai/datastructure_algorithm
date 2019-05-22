/**
 * 题目：二进制中1的个数
 * 描述：输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。
 */

#include <iostream>

// 因为对于负数（最高为1），右移时，使用符号为进行填充，所以下面的方法
// 会进入死循环
int CountOf1_V1(int num) {
    int count = 0;
    while (num != 0) {
        if (num & 0x1) {
            ++count;
        }
        num >>= 1;  // 不要借助于除法，功能没有问题，但是除法效率低
    }
    return count;
}

// 利用左移而不是右移来解决CountOf1_V1的负数问题
int CountOf1_V2(int num) {
    int count = 0;
    int base = 0x1;
    while (base) {
        if (num & base) {
            ++count;
        }
        base = base << 1;  // 右侧补零，1一直向做移动，对num对应的位进行检测
                     // 最终1会被移除，全部剩下0，退出循环
    }
    return count;
}

// 最高效的做法：元算次数等于1的个数
// num & (num-1)的结果是将最右侧的1变成0，高位不变
int CountOf1_V3(int num) {
    int count = 0;
    while (num) {
        num &= (num-1);
        ++count;
    }
    return count;
}

int main() {
    std::cout << CountOf1_V3(0) << std::endl;
    std::cout << CountOf1_V3(2) << std::endl;
    std::cout << CountOf1_V3(7) << std::endl;
    std::cout << CountOf1_V3(9) << std::endl;
    std::cout << CountOf1_V3(-1) << std::endl;

    return 0;
}
