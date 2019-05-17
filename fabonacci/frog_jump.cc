/**
 * 题目：青蛙跳台阶问题
 */

#include <iostream>
#include <cstdlib>
#include <libgen.h>

/**
 * 描述1：一个台阶总共有n级，如果一次可以跳1级，也可以跳2级。求总共有多少总跳法。
 * 分析：台阶数量   跳法
 *       1          1
 *       2          2
 *       3          3
 *       4          5
 *       5          8
 *       通过分析枚举，知道可以转换为斐波那契数列的计算问题：
 *       f(n) = f(n-1) + f(n-2), n>2
 * 时间复杂度：O(n)
 */
uint64_t JumpMethods(unsigned steps) {
    static const int result[] = {0, 1, 2};
    if (steps <= 2) {
        return result[steps];
    }

    uint64_t minus_two = result[1];
    uint64_t minus_one = result[2];
    uint64_t fib = 0;
    for (unsigned idx=3; idx<=steps; ++idx) {
        fib = minus_one + minus_two;
        minus_two = minus_one;
        minus_one = fib;
    }
    return fib;
}


/**
 * 描述2：一个台阶总共有n级，如果一次可以跳1级，也可以跳2级......它也可以跳上n级。
 *        此时该青蛙跳上一个n级的台阶总共有多少种跳法
 * 分析：台阶数量   跳法
 *       1          1
 *       2          2
 *       3          4
 *       4          8
 *       通过分析枚举，得出规律f(n) = 2ⁿ⁻¹
 */
uint64_t JumpMethods2(unsigned steps) {
    if (steps == 0) {
        return 0;
    }
    uint64_t result = 1;
    for (unsigned idx=1; idx<steps; ++idx) {
        result *= 2;
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << basename(argv[0]) << " steps" << std::endl;
        return 1;
    }

    int num = atoi(argv[1]);
    std::cout << "total method: " << JumpMethods(num) << std::endl;
    std::cout << "total method: " << JumpMethods2(num) << std::endl;

    return 0;
}
