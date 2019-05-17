/**
 * 题目：求斐波那契数列的第n项
 * 描述：现在要求输入一个整数n，请输出斐波那契数列的第n项。
 * 定义：f(0) = 0; f(1) = 1; f(n) = f(n-1) + f(n-2), n>=2
 */

#include <iostream>
#include <libgen.h>
#include <cstdlib>

// 第一种方法：递归--性能低、容易栈溢出，但是实现简单
int64_t FabonacciRecursive(unsigned num) {
    if (num < 2) {
        return num;
    }
    return FabonacciRecursive(num-1) + FabonacciRecursive(num-2);
}


// 时间复杂度：O(n)
int64_t FabonacciTraverse(unsigned num) {
    int result[] = {0, 1};
    if (num < 2) {
        return result[num];
    }

    int64_t minus_one = result[1];
    int64_t minus_two = result[0];
    int64_t fib = 0;
    for (unsigned idx=2; idx<=num; ++idx) {
        fib = minus_one + minus_two;
        minus_two = minus_one;
        minus_one = fib;
    }
    return fib;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << basename(argv[0]) << " num" << std::endl;
        return 1;
    }
    int num = atoi(argv[1]);
    std::cout << FabonacciRecursive(num) << std::endl;
    std::cout << FabonacciTraverse(num) << std::endl;

    return 0;
}
