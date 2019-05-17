/**
 * 直接利用C++的std::list来实现，std::list本身就是一个双链表
 */

#ifndef __ALGORITHM_LRU_CACHE_V3_H__
#define __ALGORITHM_LRU_CACHE_V3_H__

#include <iostream>
#include <unordered_map>
#include <list>


struct Node {
    int key_ = 0;  // key存在的意义在于hash_map，快速查询是否命中
    int value_ = 0;

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
    using NodeList = std::list<Node>;

private:
    unsigned capacity_ = 0;
    std::unordered_map<int, NodeList::iterator> mp_;
    NodeList cache_;

public:
    explicit LRUCache(unsigned capacity) : capacity_{capacity} {
        std::cout << "LRU algorithm v3" << std::endl;
    }

    LRUCache(const LRUCache &) = delete;
    LRUCache &operator=(const LRUCache &) = delete;
    LRUCache(LRUCache &&oth);
    LRUCache &operator=(LRUCache &&oth);

    int Get(int key);
    int Set(int key, int value);

    // for test
    void PrintUseCount() const {}

private:
    void MoveToFront(NodeList::iterator &it);
    void PushToFront(int key, int value);
    void PopFromTail();

    friend std::ostream &operator<<(std::ostream &, const LRUCache &);
};

#endif
