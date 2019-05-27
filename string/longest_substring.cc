/**
 * 题目：最长不含重复字符的子字符串
 * 描述：请从字符串中找出一个最长的不包含重复字符的子字符串，计算
 *       该最长子字符串的长度。假设字符串中只包含从'a'到'z'的字符。
 * 分析：最长不重复子串 可用动态规划的思想，设f(i)是从左到右在第i
 *       个位置上时 当前最长不重复子串的长度，则分两种情况：
 *       (1)第i位上的字母在左侧从未出现 f(i)=f(i-1)+1
 *       (2)在左侧出现过，此时计算上一次该字母出现位置和i之间的距离
 *       gap：
 *       第一种：gap<=f(i-1)时 f(i)=gap 此时上一次出现的位置在上一
 *               个最长不重复子串内部
 *       第二种：gap>f(-1i) 时 f(i)=f(i-1)+1
 *       综上：从左到右遍历字符串同时声明一个长度26的整型数组记录各
 *       种字母出现过的位置 
 */

#include <iostream>

int LongestSubstring(const char *str) {
    if (!str) {
        return 0;
    }

    int position[26];
    for (int idx=0; idx<26; ++idx) {
        position[idx] = -1;
    }
    int max_len = 0;
    int cur_len = 0;
    for (int idx=0; str[idx]!='\0'; ++idx) {
        int pos = str[idx] - 'a';
        if (position[pos] < 0) {
            ++cur_len;
        } else {
            // 相同字母间隔的距离
            int gap = idx-position[pos];
            if (cur_len >= gap) {  // 此时重复的字符在当前最长子串内部
                cur_len = gap;
            } else {
                ++cur_len;
            }
        }
        position[pos] = idx;
        if (max_len < cur_len) {
            max_len = cur_len;
        }
    }
    return max_len;
}

int main() {
    const char *str = "abcabcbb";
    std::cout << LongestSubstring(str) << std::endl;

    return 0;
}
