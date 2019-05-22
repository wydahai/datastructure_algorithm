/**
 * 题目：House Robber II
 * 描述：After robbing those houses on that street, the thief has found 
 *       himself a new place for his thievery so that he will not get 
 *       too much attention. This time, all houses at this place are 
 *       arranged in a circle. That means the first house is the neighbor 
 *       of the last one. Meanwhile, the security system for these houses 
 *       remain the same as for those in the previous street.
 *
 *       Given a list of non-negative integers representing the amount of 
 *       money of each house, determine the maximum amount of money you 
 *       can rob tonight without alerting the police.
 *
 * 分析：社区是一个环形，第一个房子和最后一个房子相邻。
 *       此时只需要分抢劫或不抢劫第一个的房子两种情况就可以重用上一题的解题
 *       思路了。如果抢劫了第一个房子，则最后的答案只能取不抢劫最后一个房子
 *       的情况了；而如果不抢劫第一个房子，则最后的答案应该取抢劫和不抢劫最
 *       后一个房子的最大值。
 *       circle_solution(0, n-1) = 
 *          max(nums[0]+solution(2...n-2), solution(1...n-1))
 */

#include <iostream>

int RobHouseCore(int houses[], int start, int end) {
    int previous = 0;
    int current = 0;
    for (int idx=start; idx<end; ++idx) {
        int temp = current;
        current = std::max(previous+houses[idx], current);
        previous = temp;
    }
    return current;
}

int RobHouse(int houses[], int count) {
    if (!houses || count<=0) {
        return 0;
    }
    if (count == 1) {
        return houses[0];
    }

    // 第一种情况：抢劫第一个房子，最后一个房子不能被抢
    int money1 = RobHouseCore(houses, 0, count-1);
    // 第二种情况：不抢劫第一个房子，那么最后一个房子可以抢也可以不抢
    int money2 = RobHouseCore(houses, 1, count);

    return std::max(money1, money2);
}

int main() {
    int house1[] = {2, 3, 2};
    std::cout << RobHouse(house1, sizeof(house1)/sizeof(house1[0])) 
        << std::endl;

    int house2[] = {1, 2, 3, 1};
    std::cout << RobHouse(house2, sizeof(house2)/sizeof(house2[0])) 
        << std::endl;

    return 0;
}
