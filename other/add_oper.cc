/**
 * 题目：不用加减乘除做加法运算
 * 分析：
 * （1）十进制加法分三步：(以5+17=22为例)
 *  1. 只做各位相加不进位，此时相加结果为12(个位数5和7相加不进位是2，
 *     十位数0和1相加结果是1)；
 *  2. 做进位，5+7中有进位，进位的值是10；
 *  3. 将前面两个结果相加，12+10=22
 *
 * （2）这三步同样适用于二进制位运算
 *  1.不考虑进位对每一位相加。0加0、1加1结果都是0,0加1、1加0结果都是1。
 *    这和异或运算一样；
 *  2.考虑进位，0加0、0加1、1加0都不产生进位，只有1加1向前产生一个进位。
 *    可看成是先做位与运算，然后向左移动一位；
 *  3.相加过程重复前两步，直到不产生进位为止。
 */

#include <iostream>

int Add(int first, int second) {
    int one = 0;  // 保存不进位值，异或运算结果
    int two = 0;  // 保存进位值，与运算，然后左移一位结果
    do {
        one = first ^ second;
        two = (first & second) << 1;
        first = one;
        second = two;
    } while (second != 0);
    return first;
}

int main() {
    std::cout << Add(15, 117) << std::endl;

    return 0;
}
