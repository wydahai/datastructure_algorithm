/**
 * 题目：剪绳子
 * 描述：给定一根长度为n的绳子，请把绳子剪成m段（m、n都是整数，n>1并且m>1），
 *       每段绳子的长度记为k[0],k[1],…,k[m]。
 *       请问k[0]* k[1] * … *k[m]可能的最大乘积是多少？
 * 举例：当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的
 *       最大乘积是18。
 * 分析：
 *       状态定义：设f(m)为为分割成m段时的最大乘积
 *       自顶向下进行分析，得到状态转移公式：f(n) = max(f(i) * f(n-i))，其中
 *       0 < i < n，i表示长度
 *       自下向上进行计算
 */

#include <iostream>
#include <cmath>


// 时间复杂度：O(n*n)，空间复杂度：O(n)
unsigned MaxResult(unsigned length) {
    if (length < 2) {
        return 0;
    }
    // 长度为2时，切割后的最大乘积为1：切割成1 1
    if (length == 2) {
        return 1;
    }
    // 长度为3时，切割后的最大乘积为2：切割成1 2或2 1
    if (length == 3) {
        return 2;
    }

    // 数组results中第i各元素表示把长度为i的绳子剪成若干段之后，各段长度乘积
    // 的最大值，即f(i)
    unsigned *results = new unsigned[length + 1];  // 存储最优解
    unsigned max_len = 0;
    for (unsigned idx=0; idx<4; ++idx) {
        results[idx] = idx;
    }
    // sub_len递增表示计算是从下而上的，因此在求f(i)之前，对于没一个j(0<j<i)
    // 而言，f(j)都已经求解出来了，并且结果保存在results[j]中
    // 循环：sub_len=4表示当绳子的长度为4时;
    //       sub_len=5表示当绳子的长度为5时；
    //       ......
    for (unsigned sub_len=4; sub_len<=length; ++sub_len) {
        max_len = 0;
        // 求出所有可能的f(j) * f(sub_len-j)并比较出最大值，保存到results中
        // 除以2的原因：后面的计算是重复的，假设当前绳子的长度为5，那么切成
        // 2和3与3和2的乘积是一样的，所以为了避免不必要的计算，只需要计算前
        // 半部分即可
        for (unsigned j=1; j<=sub_len/2; ++j) {
            unsigned result = results[j] * results[sub_len-j];
            if (max_len < result) {
                max_len = result;
            }
            results[sub_len] = max_len;
        }
    }

    max_len = results[length];
    delete[] results;
    return max_len;
}


// 贪心算法：
// 即选择一个能够得到乘积最大值的策略进行。当 n>=5 时，我们尽可能的剪出长度
// 为 3 的小绳子；当剩下的绳子长度为 4 时，改为把绳子剪成两段。
// 证明 :首先，当 n>=5 时，我们可以证明 2(n-2)>n 并且 3(n-3)>n。也就是说，当
// 绳子剩下的长度大于或者等于 5 的时候，我们就把它剪成长度为 3 或者 2 的绳子
// 段。另外，当 n>=5 时，3(n-3)>=2(n-2)，因此我们应该尽可能地多剪长度为3的绳
// 子段。而当 n=4 时，由于 2x2>1x3 所以应该剪成两条长度分别为 2 的绳子段。
// 时间复杂度：O(1)
unsigned MaxResultGreedy(unsigned length) {
    if (length < 2) {
        return 0;
    }
    if (length == 2) {
        return 1;
    }
    if (length == 3) {
        return 2;
    }

    // 尽可能多的剪去长度为3的绳子
    unsigned times_three = length / 3;
    // 当绳子最后剩下的长度为4时，不能再剪去长度为3的绳子，而是长度为2
    if (times_three*3 + 1 == length) {
        --times_three;
    }
    unsigned times_two = (length - times_three*3) / 2;
    return pow(3, times_three) * pow(2, times_two);
}

int main() {
    std::cout << "max_result: " << MaxResult(8) << std::endl;
    std::cout << "max_result: " << MaxResultGreedy(8) << std::endl;

    return 0;
}
