/**
 * Mathematically, a binary tree is a connected, undirected, finite graph 
 * with no cycles, and no vertex of degree greater than three.
 * 对于二叉树：
 * 1.节点u的深度（depth）就是从该节点到root节点的路径长度
 * 2.节点u的高度（height）就是从该节点到叶子节点中最长路径的长度
 * 3.若节点w在节点u到节点root的路径上，则称w是u的祖先，u是w的后代
 * 4.树的高度（height）就是从root节点到叶子节点中最长路径的长度
 * 5.有时我们把一颗树进行增强，（假想）增加外部节点（externl nodes），externl node：
 *   当一个节点没有孩子节点时认为其有一个externl node作为孩子节点，对于一颗
 *   二叉树来说，若实际节点数量为n>=1，则其外部节点（external node）的数量
 *   是n + 1
 */

#ifndef __ALGORITHM_BINARY_TREE_H__
#define __ALGORITHM_BINARY_TREE_H__

#include <cassert>


/**
 * 二叉树节点表示:
 * 对于一个二叉树来说，任意一个节点都有三个指针，分别指向parent、lchild和
 * rchild，对于root节点则其parent为nil，对于叶子节点则lchild和rchild为nil，
 * 若节点没有左孩子则lchild为nil，若没有右孩子则rchild为nil
 * 下面对于节点的表示，将Node和value进行分离
 */
template<class T>
struct BTNode {
    T *parent_ = nullptr;
    T *lchild_ = nullptr;
    T *rchild_ = nullptr;

    BTNode() = default;
    BTNode(const BTNode &oth) = default;
    BTNode& operator=(const BTNode &oth) = default;
    BTNode(BTNode &&oth) = default;
    BTNode& operator=(BTNode &&oth) = default;
};

template<class Node, class T>
struct BTNodeWithValue : public BTNode<Node> {
    T value_;
};

template<class T>
struct BTNodeType : public BTNodeWithValue<BTNodeType<T>, T> {
};


/**
 * 二叉树表示与实现
 */
template<class Node>
class BinaryTree {
protected:
    // 二叉树本身可以使用指向root节点的指针来表示
    Node *root_ = nullptr;

public:
    explicit BinaryTree() = default;
    BinaryTree(const BinaryTree &oth) = delete;
    BinaryTree& operator=(const BinaryTree &oth) = delete;
    BinaryTree(BinaryTree &&oth);
    BinaryTree& operator=(BinaryTree &&oth);
    ~BinaryTree() {
        Clear();
    }

public:
    // 递归节点的深度就是从该节点到root节点的路径长度
    size_t Depth(const Node *u) const;

    // 递归获取某节点子树的大小（二叉树中后代节点的数量）
    size_t Size(const Node *u) const;
    size_t Size() const;

    // 递归获取节点的高度就是从该节点到左右孩子节点的最大路径长度
    size_t Height(const Node *u) const;
    size_t Height() const;

    // 递归遍历二叉树
    void Traverse(Node *u);
    void Traverse();

    /**
     * 使用递归处理二叉树优点：代码短小、简单、容易理解；但是也会
     * 存在一些问题，如果二叉树的高度（height）很大，那么可能会因
     * 为递归太深耗尽栈空间，从而导致crash
     */
    // 非递归版本遍历二叉树
    void TraverseNoRecursion(Node *u);
    void TraverseNoRecursion();

    void Clear();
};


template<class Node>
size_t BinaryTree<Node>::Depth(const Node *u) const {
    size_t depth = 0;
    while (u && u!=root_) {
        u = u->parent;
        ++depth;
    }
    return depth;
}

// 使用递归实现更方便
template<class Node>
size_t BinaryTree<Node>::Size(const Node *u) const {
    if (!u) {
        return 0;
    }
    return 1 + Size(u->lchild_) + Size(u->rchild_);
}

template<class Node>
size_t BinaryTree<Node>::Size() const {
    return Size(root_);
}

template<class Node>
size_t BinaryTree<Node>::Height(const Node *u) const {
    if (!u) {
        return 0;
    }
    return std::max(Height(u->lchild_), Height(u->rchild_)) + 1;
}

template<class Node>
size_t BinaryTree<Node>::Height() const {
    return Height(root_);
}

template<class Node>
void BinaryTree<Node>::Traverse(Node *u) {
    if (!u) return;
    Traverse(u->lchild_);
    Traverse(u->rchild_);
}

template<class Node>
void BinaryTree<Node>::Traverse() {
    Traverse(root_);
}

/**
 * 深度优先遍历，基本思想
 * 如果遍历u之前遍历的节点是u->lchild，那么下一个需要遍历的节点是
 * u->rchild，如果遍历u之前遍历的节点是u->rchild，那么完成了对
 * u->subtree的遍历，则需要回到u的父节点，如果遍历u之前遍历的节点
 * 是u->parent，那么下一个需要遍历的节点是u->lchild
 *              u.parent
 *                  *
 *                  u
 *                 * *
 *                *   *
 *       u->lchild     u->rchild
 * 即：在访问本节点u时，需要首先记录上一个被访问的节点(prev)和下一
 * 个需要访问的节点(next)
 */
template<class Node>
void BinaryTree<Node>::TraverseNoRecursion(Node *u) {
    Node *curr = u;
    Node *prev = nullptr;
    Node *next = nullptr;
    while (curr) {  // 非叶子节点则继续遍历
        // 上次遍历的是curr->parent
        if (prev == curr->parent_) {
            /**如果上次访问的节点是u->parent，则本次访问后，下次
             * 需要访问的节点是：
             * 1.若u->lchild存在，则访问u->lchild
             * 2.若u->lchild不存在，u->rchild存在，则访问u->rchild
             */
            if (curr->lchild_) {
                next = curr->lchild_;
            } else if (curr->rchild_) {
                next = curr->rchild_;
            } else {
                next = curr->parent_;
            }
        } else if (prev == curr->lchild_) {
            /**
             * 如果上次访问的节点是左孩子，则当存在右孩子时应首先访问
             * 右孩子，否则访问父节点
             */
            next = curr->rchild_?curr->rchild_:curr->parent_;
        } else {
            // 如果上次访问的是右孩子，则下一个节点应该是其父节点
            next = curr->parent_;
        }
        prev = curr;  // 针对下次访问，此节点为prev
        curr = next;  // 针对本次访问，上次节点为上一次的next
    }
}

template<class T>
void BinaryTree<T>::TraverseNoRecursion() {
    TraverseNoRecursion(root_);
}

template<class Node>
void BinaryTree<Node>::Clear() {
}

#endif
