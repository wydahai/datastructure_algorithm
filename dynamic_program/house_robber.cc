/**
 * 题目：House Robber
 * 描述：You are a professional robber planning to rob houses along a street. 
 *       Each house has a certain amount of money stashed, the only constraint 
 *       stopping you from robbing each of them is that adjacent houses have 
 *       security system connected and it will automatically contact the police 
 *       if two adjacent houses were broken into on the same night.
 *
 *       Given a list of non-negative integers representing the amount of money 
 *       of each house, determine the maximum amount of money you can rob 
 *       tonight without alerting the police.
 *
 * 解答：
 *       明显的动态规划问题：从左到右抢劫，对于每间房子，其当前最大抢劫财物数为：
 *       到前前个房子的最大财物数+当前屋子财物数 or 到前一个屋的最大财物数，选取
 *       二者的最大值；也就是说要么抢当前屋子，要么不抢。
 *       每次都保存到前一个屋子的最大抢劫财物数和到当前屋子的抢劫财务数；使用两个
 *       量来保存即可，无需使用数组来保存。
 */

#include <iostream>

int RobHouse(int moneys[], int len) {
    if (!moneys || len<=0) {
        return 0;
    }
    if (len == 1) {
        return moneys[0];
    }

    int previous = moneys[0];
    int current = std::max(moneys[0], moneys[1]);
    for (int idx=2; idx<len; ++idx) {
        int temp = current;
        current = std::max(previous+moneys[idx], current);
        previous = temp;
    }

    return current;
}

int main() {
    int house1[] = {3, 8, 4};
    std::cout << RobHouse(house1, sizeof(house1)/sizeof(house1[0])) 
        << std::endl;

    int house2[] = {5, 2, 1, 3};
    std::cout << RobHouse(house2, sizeof(house2)/sizeof(house2[0])) 
        << std::endl;

    return 0;
}
