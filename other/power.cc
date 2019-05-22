/**
 * 题目：实现函数：double Power(double base, int exponent);
 */

#include <iostream>


bool g_invalid_input = false;

double PowerWithUnsignedExponent(double base, unsigned exponent) {
    if (exponent == 0) {
        return 1;
    }
    if (exponent == 1) {
        return base;
    }

    double result = PowerWithUnsignedExponent(base, exponent>>1);
    result *= result;
    if (exponent & 0x1) {
        result *= base;
    }

    return result;
}

double Power(double base, int exponent) {
    g_invalid_input = false;

    // 当指数为负数时，底数不能为0，因为不能对0取倒数
    if (base>=-0.000001 && base<=0.000001 && exponent<0) {
        g_invalid_input = true;
        return 0.0;
    }

    unsigned abs_exponent = (unsigned)exponent;
    if (exponent < 0) {
        abs_exponent = (unsigned)(-exponent);
    }
    double result = PowerWithUnsignedExponent(base, abs_exponent);
    if (exponent < 0) {
        result = 1.0 / result;
    }
    return result;
}

int main() {
    std::cout << Power(1.0, 0) << std::endl;
    std::cout << Power(2.0, 1) << std::endl;
    std::cout << Power(2.0, 2) << std::endl;
    std::cout << Power(2.0, -2) << std::endl;

    return 0;
}
