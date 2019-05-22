/**
 * 题目：Excel Sheet Column Number
 * 描述：在Excel中，用A表示第一列，B表示第二列...Z表示第26列，AA表示第27列，
 *       AB表示第28列...依次列推。请写出一个函数，输入用字母表示的列号编码，
 *       输出它是第几列。
 * 分析：这道题实际上考察的是把二十六进制表示成十进制数字，将输入的字符串先
 *       转换成字符数组，遍历数组中的每一个字符，用这个字符减去A再加1就是该
 *       位对应的十进制数，然后乘以26的相应次方，最后把这些数加起来就是结果
 *       了。
 *       可能很多人会有疑惑为什么要加1，因为十进制是用0-9表示，那么二十六进
 *       制就应该用0-25表示，但是这里是A-Z，就相当于1-26，所以算出来的数需要
 *       加1。
 */

#include <iostream>
#include <cstring>


int ExcelSheetNumber(char nums[], int len) {
    if (!nums || len<=0) {
        return 0;
    }

    int num = 0;
    for (int idx=0; idx<len; ++idx) {
        num *= 26;  // 字母是26个，所以是26进制
        num += nums[idx] - 'A' + 1;
    }
    return num;
}

int main() {
    char nums1[] = "A";
    std::cout << ExcelSheetNumber(nums1, strlen(nums1)) << std::endl;
    char nums2[] = "Z";
    std::cout << ExcelSheetNumber(nums2, strlen(nums2)) << std::endl;
    char nums3[] = "AA";
    std::cout << ExcelSheetNumber(nums3, strlen(nums3)) << std::endl;
    char nums4[] = "AB";
    std::cout << ExcelSheetNumber(nums4, strlen(nums4)) << std::endl;
    char nums5[] = "AAA";
    std::cout << ExcelSheetNumber(nums5, strlen(nums5)) << std::endl;

    return 0;
}
