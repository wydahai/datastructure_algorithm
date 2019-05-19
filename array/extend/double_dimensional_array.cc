/**
 * 题目：二维数组中的查找
 * 描述：在一个二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照
 *       从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一
 *       个整数，判断数组中是否含有该整数。
 * 解答：从右上角的元素出发：
 *       1.比他小的数必定在它的左侧，就往左找
 *       2.比他大的数必定在它的下侧，就往下找
 */

#include <iostream>

bool Find(int *matrix, int rows, int columns, int num) {
    if (!matrix || rows<=0 || columns<=0) {
        return false;
    }

    bool found = false;
    // 从最右上角开始查找：第一行的最后一列
    int row = 0;
    int column = columns - 1;
    while (row<rows && column<columns) {
        if (num < matrix[row*columns + column]) {  // 一定是在row行的左侧
            --column;
        } else if (num > matrix[row*columns + column]) {  // 一定是在row行所在列的下方
            ++row;
        } else {  // 找到了，就是当前元素
            found = true;
            break;
        }
    }
    return found;
}

int main() {
    int matrix[] = {1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15};
    int num = 7;
    std::cout << "found " << num << "? " << std::boolalpha 
        << Find(matrix, 4, 4, num) << std::endl;

    return 0;
}
