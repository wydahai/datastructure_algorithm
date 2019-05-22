/**
 * 题目：House Robber III
 * 描述：The thief has found himself a new place for his thievery again. 
 *       There is only one entrance to this area, called the "root." 
 *       Besides the root, each house has one and only one parent house. 
 *       After a tour, the smart thief realized that "all houses in this 
 *       place forms a binary tree". It will automatically contact the 
 *       police if two directly-linked houses were broken into on the 
 *       same night.
 *
 *       Determine the maximum amount of money the thief can rob tonight 
 *       without alerting the police.
 *
 *       Example 1:
 *       
 *            3
 *           / \
 *          2   3
 *           \   \ 
 *            3   1
 *       Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
 *       
 *       Example 2:
 *       
 *            3
 *           / \
 *          4   5
 *         / \   \ 
 *        1   3   1
 *       Maximum amount of money the thief can rob = 4 + 5 = 9.
 *
 * 分析：空树直接返回0；
 *       非空树，则存在两种情况：第一种情况是首先会打劫root节点；第二种情况
 *       是不会打劫root节点；取两种情况的最大值即可
 */

#include <iostream>
#include <unordered_map>
#include <vector>

struct TreeNode {
    int money_;
    TreeNode *left_child_;
    TreeNode *right_child_;

    TreeNode() 
        : money_{0}, left_child_{nullptr}, right_child_{nullptr} {}
};

int RobHouseV1(TreeNode *root) {
    if (!root) {
        return 0;
    }

    // 打劫root节点时的情况：此时不可以打劫其左右孩子，但是可以打劫左右孩子
    // 节点的左右孩子（孙子辈节点，如果全部都存在时有四个）
    int money1 = root->money_;
    if (root->left_child_) {
        money1 += (RobHouseV1(root->left_child_->left_child_) +
                   RobHouseV1(root->left_child_->right_child_));
    }
    if (root->right_child_) {
        money1 += (RobHouseV1(root->right_child_->left_child_) +  
                   RobHouseV1(root->right_child_->right_child_));
    }

    // 第二种情况：不打劫root，打劫root的左右两个孩子节点
    int money2 = RobHouseV1(root->left_child_) + RobHouseV1(root->right_child_);

    return std::max(money1, money2);
}

// RobHouseV1存在的问题是：计算root时，需要计算root->left，root-right，
// root->left->left, root->left->right, root-right->left, root->right-right
// 但是当我们进行下一步计算root-left和root->right时，还是需要计算
// root->left->left, root->left->right, root-right->left, root->right-right
// 重复计算了，可以考虑缓存，不重复计算了，转换为动态规划问题：
// 最优子结构+重复子问题
using MoneyCache = std::unordered_map<TreeNode *, int>;
int RobHouseCore(TreeNode *root, MoneyCache &cache);
int RobHouseV2(TreeNode *root) {
    if (!root) {
        return 0;
    }

    MoneyCache cache;  // 缓存已经计算出的结果
    return RobHouseCore(root, cache);
}

int RobHouseCore(TreeNode *root, MoneyCache &cache) {
    if (!root) {
        return 0;
    }

    MoneyCache::iterator it;
    if ((it=cache.find(root)) != cache.end()) {  // 查看缓存中是否已存在
        return it->second;
    }

    // 打劫root节点和孙子节点的情况
    int money1 = root->money_;
    if (root->left_child_) {
        money1 += (RobHouseCore(root->left_child_->left_child_, cache) + 
                   RobHouseCore(root->left_child_->right_child_, cache));
    }
    if (root->right_child_) {
        money1 += (RobHouseCore(root->right_child_->left_child_, cache) + 
                   RobHouseCore(root->right_child_->right_child_, cache));
    }

    // 不打劫root节点，打劫孩子节点
    int money2 = (RobHouseCore(root->left_child_, cache) + 
                  RobHouseCore(root->right_child_, cache));

    int max_money = std::max(money1, money2);
    cache[root] = max_money;  // 将计算出的最优解缓存
    return max_money;
}


// 为什么会出现重复子问题的计算？这是因为我们没有记录每个子问题的状态类别，
// 我们直到每个节点就两种情况：打劫或不打劫，但是前面两种方法都没有记录这
// 些状态信息，所以在计算时就会重复计算，此时我们考虑保存每个解的状态：打
// 劫或不打劫，用一个大小为2的数组，其中array[0]表示不包含当前节点值的最大
// 值；array[1]表示包含当前节点的最大值
std::vector<int> RobHouseCore2(TreeNode *root);
int RobHouseV3(TreeNode *root) {
    if (!root) {
        return 0;
    }

    std::vector<int> ret = RobHouseCore2(root);
    // 对于根节点只有两种选择：打劫与不打劫，选择其中最大值的情况
    return std::max(ret[0], ret[1]);
}

std::vector<int> RobHouseCore2(TreeNode *root) {
    if (!root) {
        return std::vector<int>{0, 0};
    }

    // 计算孩子节点：递归，也包括两种情况
    std::vector<int> left = RobHouseCore2(root->left_child_);
    std::vector<int> right = RobHouseCore2(root->right_child_);

    std::vector<int> ret(2, 0);
    // 不打劫此节点：则分别取左右孩子中的最大值
    ret[0] = std::max(left[0], left[1]) + std::max(right[0], right[1]);
    // 打劫此节点：则说明不能打劫左右孩子节点，所以都取第一个元素
    ret[1] = left[0] + right[0] + root->money_;
    return ret;
}

void ReleaseTree(TreeNode *root) {
    if (!root) {
        return;
    }
    ReleaseTree(root->left_child_);
    ReleaseTree(root->right_child_);
    delete root;
}

int main() {
    TreeNode *root = new TreeNode;
    root->money_ = 3;
    root->left_child_ = new TreeNode;
    root->left_child_->money_ = 2;
    root->right_child_ = new TreeNode;
    root->right_child_->money_ = 3;
    root->left_child_->right_child_ = new TreeNode;
    root->left_child_->right_child_->money_ = 3;
    root->right_child_->right_child_ = new TreeNode;
    root->right_child_->right_child_->money_ = 1;
    // std::cout << RobHouseV1(root) << std::endl;
    // std::cout << RobHouseV2(root) << std::endl;
    std::cout << RobHouseV3(root) << std::endl;

    TreeNode *root2 = new TreeNode;
    root2->money_ = 3;
    root2->left_child_ = new TreeNode;
    root2->left_child_->money_ = 4;
    root2->right_child_ = new TreeNode;
    root2->right_child_->money_ = 5;
    root2->left_child_->left_child_ = new TreeNode;
    root2->left_child_->left_child_->money_ = 1;
    root2->left_child_->right_child_ = new TreeNode;
    root2->left_child_->right_child_->money_ = 3;
    root2->right_child_->right_child_ = new TreeNode;
    root2->right_child_->right_child_->money_ = 1;
    // std::cout << RobHouseV1(root2) << std::endl;
    // std::cout << RobHouseV2(root2) << std::endl;
    std::cout << RobHouseV3(root2) << std::endl;

    ReleaseTree(root);
    ReleaseTree(root2);

    return 0;
}
