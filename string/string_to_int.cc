/**
 * 题目：字符串转换为数字
 */

#include <iostream>

enum Status {kValid=0, kInvalid};
int g_status = kValid;

int64_t StrToIntCore(const char *digit, bool minus) {
    int64_t num = 0;
    while (*digit != '\0') {
        if (*digit>='0' && *digit<='9') {
            num = num*10 + *digit-'0';
            // 溢出：正整数的最大值是0x7FFFFFFF，最小的负数是0x80000000
            if ((!minus && num>0x7FFFFFFF) || 
                (minus && num<(signed int)0x80000000)) {
                num = 0;
                break;
            }
            ++digit;
        } else {
            num = 0;
            break;
        }
    }

    if (*digit == '\0') {
        g_status = kValid;
    }

    return minus?-num:num;
}

int StrToInt(const char *str) {
    g_status = kInvalid;
    int64_t num = 0;

    if (str && *str!='\0') {
        bool minus = false;
        if (*str == '+') {
            ++str;
        } else if (*str == '-') {
            minus = true;
            ++str;
        }

        if (*str != '\0') {
            num = StrToIntCore(str, minus);
        }
    }

    return (int)num;
}

int main() {
    std::cout << StrToInt("123") << std::endl;
    std::cout << StrToInt("-123") << std::endl;
    std::cout << StrToInt("-0") << std::endl;

    return 0;
}
