/**
 * 题目：员工年龄排序
 * 描述：对公司所有员工的年龄进行排序，公司总共有几万名员工，要求时间复杂度为O（n）
 * 分析：很明显的计数排序题目，员工的年龄肯定在一个范围之内，我们这里假设在0-99之内，
 *       算很大了，这样就可以开辟一个长度为100的数组，保存各个年龄的员工的个数
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 * 关键点是排序的范围很小：0 ~ 99，充分利用这一点
 */

#include <iostream>


void SortByAge(int ages[], int len) {
    if (!ages || len<=0) {
        return;
    }

    // 借助一块辅助的空间，用来存储每个年龄有多少员工，年龄就是下标
    constexpr int oldest_age = 99;
    int count_ages[oldest_age+1];  // 年龄范围：0 ~ 99
    for (int idx=0; idx<=oldest_age; ++idx) {
        count_ages[idx] = 0;
    }

    // 统计每个年龄有多少员工
    for (int idx=0; idx<len; ++idx) {
        if (ages[idx]<0 || ages[idx]>99) {
            std::cerr << "bad age: " << ages[idx] << std::endl;
            continue;
        }
        ++count_ages[ages[idx]];
    }

    // 对年龄进行排序，此时年龄已经是在count_ages中有序的了，因为count_ages
    // 的下标就是年龄，从0～99，但是每个年龄可能对应多个员工，现在就是按照此
    // 顺序展开即可
    int idx = 0;
    for (int age=0; age<=oldest_age; ++age) {
        // 每个年龄可能存在多个员工，需要展开、顺序存储到age中
        for (int i=0; i<count_ages[age]; ++i) {
            ages[idx++] = age;
        }
    }
}

int main() {
    int ages[] = {33,34,45,24,36,23,21,22,19,26,45,34,21,
        34,34,33,52,22,32,25,27,43,22,21,20,33,26,27,15,29};
    int len = sizeof(ages)/sizeof(ages[0]);
    SortByAge(ages, len);
    for (int idx=0; idx<len; ++idx) {
        std::cout << ages[idx] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
