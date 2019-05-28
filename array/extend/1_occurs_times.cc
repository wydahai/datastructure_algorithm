/**
 * 题目：从1到n整数中1出现的次数
 * 描述：输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。
 *       例如输入12，从1到12这些整数中包含1的数字有1，10，11和12，1
 *       一共出现了5次。
 */

#include <iostream>

/**
 * 解法：https://blog.csdn.net/yi_afly/article/details/52012593
 *       感觉比剑指offer简单
 */
int Count1Numbers(int num) {
    if (num < 1) {
        return 0;
    }
    int count = 0;
    int base = 1;
    int round = num;
    while (round > 0) {
        int weight = round % 10;
        round /= 10;
        count += round * base;
        if (weight == 1) {
            count += (num%base) + 1;
        } else if (weight > 1) {
            count += base;
        }
        base *= 10;
    }

    return count;
}

int main() {
    return 0;
}
