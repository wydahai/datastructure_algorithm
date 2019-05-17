/**
 * 针对V1版本的改进：V1版本中要删除一个节点，因为是单链表所以
 * 时间复杂度是O(n)，改进版本的时间复杂度为O(1)，同时删除尾部
 * 元素的改进方案是：LRUCache维护一个指向尾部节点的指针
 */

#ifndef __ALGORITHM_LRU_CACHE_V2_H__
#define __ALGORITHM_LRU_CACHE_V2_H__

#include <memory>
#include <unordered_map>
#include <iostream>


// 由单链表改成双链表
struct Node {
    int key_ = 0;
    int value_ = 0;
    std::shared_ptr<Node> next_ = nullptr;
    // 因为存在next和prev存在循环引用的问题，所以prev_声明为weak_ptr
    std::weak_ptr<Node> prev_{};

    explicit Node() = default;
    explicit Node(int key, int value) : key_{key}, value_{value} {}
    //~Node() {
    //    std::cout << "delete node: " << key_ << std::endl;
    //}
};

class LRUCache;
std::ostream &operator<<(std::ostream &, const LRUCache &);

class LRUCache {
private:
    unsigned capacity_ = 0;
    unsigned size_ = 0;
    // 用于保存已存在的key及Node*，可以O(1)判读key是否存在及读取其值
    std::unordered_map<int, std::shared_ptr<Node>> mp_;
    // 带头节点的链表头指针
    std::unique_ptr<Node> header_ = nullptr;
    // 指向链表尾节点：便于快速的删除表尾节点
    std::shared_ptr<Node> tail_ = nullptr;

public:
    LRUCache(unsigned capacity) 
        : capacity_{capacity}, header_{std::make_unique<Node>()}{
        std::cout << "LRU algorithm v2" << std::endl;
    }

    //~LRUCache() {}

    int Set(int key, int value);
    int Get(int key);


    // for test
    void PrintUseCount() const;

private:
    void MoveToFront(std::shared_ptr<Node> &node);
    void PopFromTail();
    void PushToFront(int key, int value);

    friend std::ostream &operator<<(std::ostream &, const LRUCache &);
};

#endif  // __ALGORITHM_LRU_CACHE_V2_H__
