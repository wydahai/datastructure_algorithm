#include <cassert>

#include "lru_cache_v1.h"


int LRUCache::Get(int key) {
    if (!cache_list_->next_ || size_==0) {
        return -1;
    }
    auto it = mp_.find(key);
    if (it == mp_.end()) {
        return -1;
    }
    MoveToFront(it->second);  // 访问后需要将该数据项放置表头
    return it->second->value_;
}

int LRUCache::Set(int key, int value) {
    auto it = mp_.find(key);
    if (it != mp_.end()) {  // 如果数据项已存在则直接更新
        it->second->value_ = value;
        MoveToFront(it->second);
        return 0;
    }

    // 如果数据项不存在则插入
    // 判断cache是否已满，若满则需要删除链表尾部元素
    if (size_ >= capacity_) {
        PopTail();
    }
    return PushFront(key, value);
}

void LRUCache::MoveToFront(std::shared_ptr<Node> &node) {
    assert(cache_list_->next_);
    if (node == cache_list_->next_) {
        return;
    }
    auto ptr = cache_list_->next_;
    while (ptr->next_) {  // 定位要移动的node：瓶颈
        if (ptr->next_ == node) {
            ptr->next_ = node->next_;  // 在链表中删除该节点
            break;
        }
        ptr = ptr->next_;
    }
    // 将已在链表中删除的node节点插入到表头
    node->next_ = cache_list_->next_;
    cache_list_->next_ = node;
}

void LRUCache::PopTail() {
    assert(cache_list_->next_);
    --size_;
    auto node = cache_list_->next_;
    if (!(node->next_)) {  // 链表中只有一个node
        cache_list_->next_ = nullptr;
        mp_.erase(node->key_);
        return;
    }
    while (node->next_->next_) {  // 找到链表尾部节点之前的节点：瓶颈
        node = node->next_;
    }
    mp_.erase(node->next_->key_);
    node->next_ = nullptr;
}

int LRUCache::PushFront(int key, int value) {
    auto node = std::make_shared<Node>(key, value);
    // 将node插入到表头，即使是一个空表也是没有问题的
    node->next_ = cache_list_->next_;
    cache_list_->next_ = node;
    mp_[key] = node;
    ++size_;
    return 0;
}

void LRUCache::PrintUseCount() const {
    auto node = cache_list_->next_;
    while (node) {
        std::cout << "key: " << node->key_ 
            << ", use_count: " << node.use_count() << std::endl;
        node = node->next_;
    }
}

std::ostream &operator<<(std::ostream &os, const LRUCache &cache) {
    os << "cache traverse:" << std::endl;
    auto node = cache.cache_list_->next_;
    while (node) {
        os << "key: " << node->key_ 
            << ", value: " << node->value_ << std::endl;
        node = node->next_;
    }
    return os;
}
