#include <cassert>

#include "lru_cache_v3.h"


std::ostream &operator<<(std::ostream &os, const LRUCache &cache) {
    std::cout << "cache traverse:" << std::endl;
    for (const auto &node : cache.cache_) {
        std::cout << "key: " << node.key_ 
            << ", value: " << node.value_ << std::endl;
    }
    return os;
}

int LRUCache::Get(int key) {
    auto it = mp_.find(key);
    if (it == mp_.end()) {
        return -1;
    }
    MoveToFront(it->second);
    return it->second->value_;
}

int LRUCache::Set(int key, int value) {
    auto it = mp_.find(key);
    if (it != mp_.end()) {  // 存在则更新value，且移动到表头
        it->second->value_ = value;
        MoveToFront(it->second);
    } else {  // 不存在则新建Node并插入到表头
        if (cache_.size() >= capacity_) {
            PopFromTail();
        }
        PushToFront(key ,value);
    }
    return 0;
}

void LRUCache::MoveToFront(NodeList::iterator &it) {
    assert(cache_.size() > 0);

    auto node = std::move(*it);
    cache_.erase(it);
    int key = node.key_;
    cache_.emplace_front(std::move(node));
    mp_[key] = cache_.begin();
}

void LRUCache::PushToFront(int key, int value) {
    cache_.emplace_front(key, value);
    mp_[key] = cache_.begin();
}

void LRUCache::PopFromTail() {
    mp_.erase(cache_.back().key_);
    cache_.pop_back();
}
