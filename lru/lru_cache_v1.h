/**
 * 实现：利用链表和hashmap。当需要插入新的数据项的时候，如果新数据项在链表中
 * 存在（一般称为命中），则把该节点移到链表头部，如果不存在，则新建一个节点，
 * 放到链表头部，若缓存满了，则把链表最后一个节点删除即可。在访问数据的时候，
 * 如果数据项在链表中存在，则把该节点移到链表头部，否则返回-1。这样一来在链表
 * 尾部的节点就是最近最久未访问的数据项。
 */
#ifndef __ALGORITHM_LRU_CACHE_V1_H__
#define __ALGORITHM_LRU_CACHE_V1_H__


#include <unordered_map>
#include <memory>
#include <iostream>

struct Node {  // 单链表
    int key_ = 0;
    int value_ = 0;
    std::shared_ptr<Node> next_ = nullptr;

    explicit Node() = default;

    Node(int key, int value) : key_{key}, value_{value} {}
    //~Node() {
    //    std::cout << "delete node: " << key_ << std::endl;
    //}
};


class LRUCache {
private:
    unsigned capacity_ = 0;  // 由调用者保证capacity_>=1
    unsigned size_ = 0;
    // 用于判断数据项是否已在缓存中，此处使用hash_map好处是查找ke是否存在
    // 的时间复杂度O(1)，而map是log2N
    std::unordered_map<int, std::shared_ptr<Node>> mp_;
    // 每次数据项被访问，则将其放置表头，这样表尾就是所有数据项中
    // 最近未被访问的元素(最长时间未被访问的数据项)
    std::unique_ptr<Node> cache_list_ = nullptr;  // 数据项链表

public:
    explicit LRUCache(unsigned capacity) 
        : capacity_{capacity}, cache_list_{std::make_unique<Node>()} {
        std::cout << "LRU algorithm v1" << std::endl;
    }
    ~LRUCache() {}
    LRUCache(const LRUCache &) = delete;
    LRUCache &operator=(const LRUCache &) = delete;
    LRUCache(LRUCache &&oth);
    LRUCache &operator=(LRUCache &&oth);

    int Get(int key);
    int Set(int key, int value);

    // for test
    void PrintUseCount() const;

private:
    void MoveToFront(std::shared_ptr<Node> &node);
    int PushFront(int key, int value);
    void PopTail();


    friend std::ostream &operator<<(std::ostream &, const LRUCache &);
};

std::ostream &operator<<(std::ostream &, const LRUCache &);

#endif  // __ALGORITHM_LRU_CACHE_V1_H__
