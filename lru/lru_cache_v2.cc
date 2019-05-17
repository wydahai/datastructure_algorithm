#include <cassert>

#include "lru_cache_v2.h"


std::ostream &operator<<(std::ostream &os, const LRUCache &cache) {
    os << "cache traverse:" << std::endl;
    auto node = cache.header_->next_;
    while (node) {
        std::cout << "key: " << node->key_ 
            << ", value: " << node->value_ << std::endl;
        node = node->next_;
    }
    return os;
}

int LRUCache::Get(int key) {
    auto it = mp_.find(key);
    if (it == mp_.end()) {
        return -1;
    }
    MoveToFront(it->second);  // 更新访问：将该node移动到表头
    return it->second->value_;
}

int LRUCache::Set(int key, int value) {
    auto it = mp_.find(key);
    if (it != mp_.end()) {  // key已存在，更新，并move
        it->second->value_ = value;
        MoveToFront(it->second);
    } else {  // key不存在，则插入到cache中
        if (size_ >= capacity_) {  // cache已满，需要清除最近最少使用node
            PopFromTail();
        }
        PushToFront(key, value);
    }
    return 0;
}

void LRUCache::MoveToFront(std::shared_ptr<Node> &node) {
    assert(header_->next_);

    // std::shared_ptr比较的是指针值，不是指向的对象
    if (header_->next_ == node) {  // 是链表中第一个node
        return;
    }
    // 双向链表：删除node，node的前驱node的next指向node的后继；
    // node的后继node的prev指向node的前驱
    node->prev_.lock()->next_ = node->next_;  // 不判断lock的返回值了
    if (node->next_) {  // node不是最后一个节点
        node->next_->prev_ = node->prev_;
    } else {  // node是最后一个节点，tail_需要指向node的前驱
        tail_ = node->prev_.lock();
    }
    // 将该node插入到表头
    header_->next_->prev_ = node;
    node->next_ = header_->next_;
    header_->next_ = node;
    node->prev_.reset();
}

void LRUCache::PopFromTail() {
    assert(header_->next_);

    --size_;
    mp_.erase(tail_->key_);
    if (header_->next_ == tail_) {  // 当前链表中只有一个node
        header_->next_ = nullptr;
        tail_ = nullptr;
    } else {
        tail_ = tail_->prev_.lock();  // tail_指向倒数第二个node
        tail_->next_->prev_.reset();
        tail_->next_ = nullptr;
    }
}

void LRUCache::PushToFront(int key, int value) {
    auto node = std::make_shared<Node>(key, value);
    ++size_;
    mp_[key] = node;
    if (!header_->next_ && !tail_) {  // 空链表
        header_->next_ = node;
        tail_ = node;  // 尾指针指向新创建的node
    } else {
        header_->next_->prev_ = node;
        node->next_ = header_->next_;
        header_->next_ = node;
    }
}

void LRUCache::PrintUseCount() const {
    auto node = header_->next_;
    while (node) {
        std::cout << "key: " << node->key_ 
            << ", use_count: " << node.use_count() << std::endl;
        node = node->next_;
    }
}
