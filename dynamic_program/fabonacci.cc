/**
 * 题目：计算第n项斐波那契数
 * 要求：利用动态规划方法
 * 动态规划：dynamic programming is a method for solving a complex problem 
 *           by breaking it down into a collection of simpler subproblems, 
 *           solving each of those subproblems just once, and storing their 
 *           solutions.
 *           三要素：1.分解；2.只计算一次；3.记忆(存储)
 *           状态定义：f(n)为第n项斐波那契的状态
 *           状态转移：f(n) = f(n-1) + f(n-2), f(0) = 0, f(1) = f(2) = 1
 */

#include <iostream>

uint64_t Fabonacci(unsigned max_num) {
    if (max_num <= 1) {
        return max_num;
    }

    uint64_t minus_one = 0;  // num = 0
    uint64_t minus_two = 1;  // num = 1
    uint64_t fib_num = 0;
    for (unsigned num=2; num<=max_num; ++num) {
        fib_num = minus_one + minus_two;
        minus_two = minus_one;
        minus_one = fib_num;
    }
    return fib_num;
}

int main() {
    std::cout << Fabonacci(5) << std::endl;
    std::cout << Fabonacci(7) << std::endl;

    return 0;
}
