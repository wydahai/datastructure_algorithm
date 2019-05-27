/**
 * 题目：打印1到最大的n位数
 * 描述：输入数字n，按顺序打印出从1到最大的n位十进制数。比如输入3，则打印出1，2，3，
 *       一直到最大的3位数即999。 
 * 分析：数据超出类型范围就会溢出，用字符串表示大数在字符串上模拟数字加法的解法。字
 *       符串里每个字符都是‘0’到‘9’之间的数字。因为数字最大时n位的，所以需要长度n+1
 *       的字符串。当实际数字不够n位时在字符串前半部分补0。
 */

#include <iostream>
#include <cstring>

bool IncrementNumber(char *number) {
    bool is_over_flow = false;
    int take_over = 0;  // 表示需要进位的值
    int length = strlen(number);
    for (int i=length-1; i>=0; --i) {
        // 第一次循环时的值是当前最后一位的数值，此时的take_over=0
        int sum = number[i] - '0' + take_over;
        if (i == length-1) {  // 因为是按照顺序输出，所以每次都是最后一位加1
            ++sum;
        }

        // 下面的逻辑是判断进位情况
        if (sum >= 10) {
            if (i == 0) {  // 只有最高位需要进位时才会溢出
                is_over_flow = true;
            } else {
                sum -= 10;
                take_over = 1;
                number[i] = sum + '0';
            }
        } else {  // 没有产生进位
            number[i] = sum + '0';
            break;
        }
    }

    return is_over_flow;  // 溢出后说明已经打印完毕所有的数字
}

void PrintNumber(char *number) {
    char *top_bit_pos = number;
    while (*top_bit_pos == '0') {
        ++top_bit_pos;
    }
    std::cout << top_bit_pos << '\t';
}

void PrintMaxNDigits(int n) {
    if (n <= 0) {
        return;
    }

    char *number = new char[n+1];  // 使用字符串来表示数字
    memset(number, '0', n);  // 需要全部都初始化为0
    number[n] = '\0';

    while (!IncrementNumber(number)) {
        PrintNumber(number);
    }
    std::cout << std::endl;

    delete[] number;
}

void PrintMaxNDigitsRecursively(char *number, int length, int index) {
    if (index == length - 1) {  // 已经计算处最开始的那一位
        PrintNumber(number);
        return;
    }

    for (int i=0; i<10; ++i) {
        number[index+1] = '0' + i;
        PrintMaxNDigitsRecursively(number, length, index+1);
    }
}

// 递归版本，思想就是每一位只能是0-9，循环打印即可
void PrintMaxNDigits_V2(int n) {
    if (n < 0) {
        return;
    }

    char *number = new char[n+1];
    number[n] = '\0';

    for (int i=0; i<10; ++i) {  // 此循环是打印最高位的可能数值：0 ～ 9
        number[0] = '0' + i;
        PrintMaxNDigitsRecursively(number, n, 0);
    }
    std::cout << std::endl;

    delete[] number;
}

int main() {
    PrintMaxNDigits(3);
    PrintMaxNDigits_V2(3);

    return 0;
}
