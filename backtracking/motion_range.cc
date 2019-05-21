/**
 * 题目：机器人的运动范围
 * 描述：地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能
 *       向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大
 *       于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为
 *       3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机
 *       器人能够达到多少个格子？
 * 分析：机器人从坐标（0，0）开始移动，当它准备进入坐标为（i，j）的格子时，通过检
 *       查坐标的数位和来判断机器人是否能够进入（之前是判断字符是否相同）。如果能
 *       够进入（i，j），则判断它的四个相邻的格子。递归实现。
 */

#include <iostream>


int MoveCountCore(int threshold, int rows, int cols, 
                  int row, int col, bool *visited);
// 用于判断位置(row, col)是否可以进入
bool Check(int threshold, int rows, int cols, 
           int row, int col, bool *visited);
int GetDigitSum(int num);  // 计算num各位上数字之和

int MoveCount(int threshold, int rows, int cols) {
    if (threshold<0 || rows<1 || cols<1) {
        return 0;
    }

    // 用于标记该位置是否已经被访问过
    bool *visited = new bool[rows * cols];
    for (int idx=0; idx<rows*cols; ++idx) {
        visited[idx] = false;
    }

    int count = MoveCountCore(threshold, rows, cols, 0, 0, visited);

    delete[] visited;
    return count;
}

int MoveCountCore(int threshold, int rows, int cols, 
                  int row, int col, bool *visited) {
    int count = 0;
    if (Check(threshold, rows, cols, row, col, visited)) {
        visited[row * cols + col] = true;
        // 加1的原因是本次check通过了
        ++count;
        count += (MoveCountCore(threshold, rows, cols, row, col-1, visited) + 
                  MoveCountCore(threshold, rows, cols, row, col+1, visited) + 
                  MoveCountCore(threshold, rows, cols, row-1, col, visited) + 
                  MoveCountCore(threshold, rows, cols, row+1, col, visited));
    }
    return count;
}

bool Check(int threshold, int rows, int cols, 
           int row, int col, bool *visited) {
    if (row>=0 && row<rows && col>=0 && col<cols && 
        !visited[row*cols+col] && 
        (GetDigitSum(row)+GetDigitSum(col)<=threshold)) {
        return true;
    }
    return false;
}

int GetDigitSum(int num) {
    int sum = 0;
    while (num > 0) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int main() {
    int threshold = 18;
    int rows = 100;
    int cols = 100;
    std::cout << MoveCount(threshold, rows, cols) << std::endl;

    return 0;
}
