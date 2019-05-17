/**
 * 题目：替换空格
 * 描述：请实现一个函数，将一个字符串中的空格替换成“%20”。例如，当字符串为
 *       We Are Happy，则经过替换之后的字符串为We%20Are%20Happy。
 * 解答：首先遍历字符串计算出字符串的总长度和空格的数量，这样就可以计算出
 *       新字符串的总长度：orgin_len + num_blanks * 2(原有一个空格字符，现
 *       在是在原来的基础上增加了2个字符（实际长度是3个字符）)，然后从后向
 *       前的方向复制子串，遇到空格时替换
 *       从后开始移动，相对于从前向后移动会减少移动次数
 *       时间复杂度O(n)
 */

#include <iostream>
#include <cstring>


void ReplaceBlank(char string[], int length) {
    if (!string || length <= 0) {
        return;
    }

    // 首先计算字符串的总长度和空格的数量
    int origin_len = 0;
    int blanks_count = 0;
    while (string[origin_len] != '\0') {
        ++origin_len;
        if (string[origin_len] == ' ') {
            ++blanks_count;
        }
    }

    int current_len = origin_len + blanks_count * 2;  // 替换后字符串长度
    std::cout << "blanks_count: " << blanks_count << std::endl;
    std::cout << "current_len: " << current_len << std::endl;
    if (current_len > length) {
        return;
    }

    // 如果没有空格，则current_len == origin_len，不需要移动替换
    while (origin_len>=0 && current_len>origin_len) {
        if (string[origin_len] == ' ') {  // 不要忘记移动最后的'\0'，所以不减1
            string[current_len--] = '%';
            string[current_len--] = '0';
            string[current_len--] = '2';
        } else {
            string[current_len--] = string[origin_len];
        }
        --origin_len;
    }
}


int main() {
    char origin[24] = "We are hapy.";
    ReplaceBlank(origin, sizeof(origin));
    std::cout << origin << std::endl;

    return 0;
}
