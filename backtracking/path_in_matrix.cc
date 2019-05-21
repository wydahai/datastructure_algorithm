/**
 * 题目：矩阵中的路径
 * 描述：请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
 *       路径可以从矩阵中任意一格开始，每一步可以在矩阵中间向左、右、上、下移动一格。
 *       如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。
 * 分析：
 *       举例：
 *       a   b   t   g
 *       c   f   c   s
 *       j   d   e   h
 *       回溯算法的基本实现思想可以理解为一个栈，遇到不满足条件时，弹出栈进行下一个
 *       选择的探测，重复此过程直到遇到满足条件或全部不满足条件为止。
 */

#include <iostream>
#include <cstring>


bool HasPathCore(const char *matrix, int rows, int cols, 
                 int row, int col, const char *str, 
                 int path_length, bool *visited);

// 在matrix中查找str的路径，matrix的大小是rows行，cols列
bool HasPath(char *matrix, int rows, int cols, char *str) {
    if (!matrix || rows<1 || cols<1 || !str) {
        return false;
    }

    bool *visited = new bool[rows*cols];  // 用于记录某个位置是否已访问过
    memset(visited, 0x0, rows*cols);

    int path_length = 0;
    for (int row=0; row<rows; ++row) {
        for (int col=0; col<cols; ++col) {
            if (HasPathCore(matrix, rows, cols, row, col, str, 
                            path_length, visited)) {
                delete[] visited;
                return true;
            }
        }
    }

    delete[] visited;
    return false;
}

bool HasPathCore(const char *matrix, int rows, int cols, 
                 int row, int col, const char *str, 
                 int path_length, bool *visited) {
    if (str[path_length] == '\0') {
        return true;
    }

    bool has_path = false;
    long long visite_idx = row * cols + col;
    if (row>=0 && row<rows && col>=0 && col<cols && 
        matrix[visite_idx]==str[path_length] && !visited[visite_idx]) {
        ++path_length;  // 判断下一个字符
        visited[visite_idx] = true;  // 标记该位置已经被访问过

        // 判断下一个字符是否满足条件，在矩阵中每个位置有四个方向可以考虑
        // 对于边界通过col、row与cols、rows的大小比较来控制
        has_path = (HasPathCore(matrix, rows, cols, row, col-1, 
                                str, path_length, visited) || 
                    HasPathCore(matrix, rows, cols, row, col+1, 
                                str, path_length, visited) || 
                    HasPathCore(matrix, rows, cols, row-1, col, 
                                str, path_length, visited) || 
                    HasPathCore(matrix, rows, cols, row+1, col, 
                                str, path_length, visited));
        if (!has_path) {
            --path_length;
            // 如果校验失败，需要取消之前标记过已访问的位置
            visited[visite_idx] = false;
        }
    }

    return has_path;
}

int main() {
    char matrix[] = {'a', 'b', 'c', 'e', 's', 'f', 'c', 's', 'a', 'd', 'e', 'e'};
    
    char first[] = "bfce";
    std::cout << std::boolalpha << HasPath(matrix, 3, 4, first) << std::endl;
    char second[] = "abfb";
    std::cout << std::boolalpha << HasPath(matrix, 3, 4, second) << std::endl;

    return 0;
}
