#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__


#include <memory>
#include <iostream>


template <typename T>
struct SLListNode {
    T data_{};
    std::shared_ptr<SLListNode> next_{nullptr};

    explicit SLListNode() = default;

    explicit SLListNode(const T &data) : data_{data} {
        std::cout << "create a new node(lvalue): " << data_ << std::endl;
    }

    explicit SLListNode(T &&data) : data_{std::move(data)} {
        std::cout << "create a new node(rvalue): " << data_ << std::endl;
    }

    explicit SLListNode(const T &data, std::shared_ptr<SLListNode> &next) 
        : data_{data}, next_{next} {
        std::cout << "create a new node(lvalue): " << data_ << std::endl;
    }

    explicit SLListNode(T &&data, std::shared_ptr<SLListNode> &next) 
        : data_{data}, next_{next} {
        std::cout << "create a new node(rvalue): " << data_ << std::endl;
    }

    ~SLListNode() {
        std::cout << "destroy the node: " << data_ << std::endl;
    }

    explicit SLListNode(const SLListNode &) = default;
    SLListNode &operator=(const SLListNode &) = default;
    explicit SLListNode(SLListNode &&) = default;
    SLListNode &operator=(SLListNode &&) = default;
};

template <typename T>
class SLinkedList;

template <typename T>
std::ostream &operator<<(std::ostream &, const SLinkedList<T> &);

template <typename T>
class SLinkedList {
private:
    std::shared_ptr<SLListNode<T>> head_{nullptr};
    size_t size_{0};

public:
    explicit SLinkedList() 
        : head_{std::make_shared<SLListNode<T>>()} {
        std::cout << "create a new singly linked list" << std::endl;
    }

    ~SLinkedList() {
        std::cout << "destory the singly linked list: " << head_ << std::endl;
    }

    SLinkedList(const SLinkedList &) = delete;
    SLinkedList &operator=(const SLinkedList &) = delete;
    SLinkedList(SLinkedList &&) = default;
    SLinkedList &operator=(SLinkedList &&) = default;

public:
    inline size_t Size() const;
    inline bool Empty() const;

    bool Insert(size_t pos, const T &data);
    bool Insert(size_t pos, T &&data);
    bool Insert(const std::shared_ptr<SLListNode<T>> &pos, const T &data);
    bool Insert(const std::shared_ptr<SLListNode<T>> &pos, T &&data);
    bool PushFront(const T &data);
    bool PushFront(T &&data);
    bool PushBack(const T &data);
    bool PushBack(T &&data);

    const std::shared_ptr<SLListNode<T>> &Get(size_t idx) const;
    std::shared_ptr<SLListNode<T>> &Get(size_t idx);
    const std::shared_ptr<SLListNode<T>> &GetFront() const;
    std::shared_ptr<SLListNode<T>> &GetFront();
    const std::shared_ptr<SLListNode<T>> &GetBack() const;
    std::shared_ptr<SLListNode<T>> &GetBack();

    void Remove(const T &data);
    void Remove(SLListNode<T> *pos);
    void PopFront();
    void PopBack();

    void Clear();

    template <typename T1>
    friend std::ostream &operator<<(std::ostream &, const SLinkedList<T1> &);
};

template <typename T>
size_t SLinkedList<T>::Size() const {
    return size_;
}

template <typename T>
bool SLinkedList<T>::Empty() const {
    return size_?false:true;
}

template <typename T>
bool SLinkedList<T>::Insert(size_t pos, const T &data) {
    std::cout << "call lvalue reference version" << std::endl;
    if (pos > size_) {
        return false;
    }
    // 单链表的传统插入方法需要将某个节点之前插入转换为此节点的直接前驱节点之
    // 后的插入
    auto prev_node = head_;
    for (size_t idx=0; idx<pos; ++idx) {  // idx<pox：定位到直接前驱节点
        prev_node = prev_node->next_;
    }
    auto new_node = std::make_shared<SLListNode<T>>(data, prev_node->next_);
    prev_node->next_ = new_node;
    ++size_;
    return true;
}

template <typename T>
bool SLinkedList<T>::Insert(size_t pos, T &&data) {
    std::cout << "call rvalue reference version" << std::endl;
    if (pos > size_) {
        return false;
    }
    auto prev_node = head_;
    for (size_t idx=0; idx<pos; ++idx) {  // idx<pox：定位到直接前驱节点
        prev_node = prev_node->next_;
    }
    prev_node->next_ = std::make_shared<SLListNode<T>>(std::move(data), 
                                                       prev_node->next_);
    ++size_;
    return true;
}

template <typename T>
bool SLinkedList<T>::Insert(const std::shared_ptr<SLListNode<T>> &pos, 
                            const T &data) {
    // 单链表的传统插入方法需要将某个节点之前插入转换为此节点的直接前驱节点之
    // 后的插入，时间复杂度O(n)
    // 如果想要时间复杂度为O(1)，则把新节点插入到pos之后，然后交换两个节点的
    // data_
    if (!pos->next_) {  // 尾节点没有后继节点，所以需要单独考虑
        auto prev_node = head_;
        while (prev_node->next_) {
            prev_node = prev_node->next_;
        }
        prev_node->next_ = std::make_shared<SLListNode<T>>(data, nullptr);
    } else {
        auto new_node = std::make_shared<SLListNode<T>>(data, pos->next_);
        pos->next_ = new_node;
        std::swap(pos->data_, new_node->data_);
    }
    return true;
}

template <typename T>
bool SLinkedList<T>::Insert(const std::shared_ptr<SLListNode<T>> &pos, 
                            T &&data) {
    // 单链表的传统插入方法需要将某个节点之前插入转换为此节点的直接前驱节点之
    // 后的插入，时间复杂度O(n)
    // 如果想要时间复杂度为O(1)，则把新节点插入到pos之后，然后交换两个节点的
    // data_
    if (!pos->next_) {  // 尾节点没有后继节点，所以需要单独考虑
        auto prev_node = head_;
        while (prev_node->next_) {
            prev_node = prev_node->next_;
        }
        prev_node->next_ = std::make_shared<SLListNode<T>>(std::move(data), 
                                                           nullptr);
    } else {
        auto new_node = std::make_shared<SLListNode<T>>(std::move(data), 
                                                        pos->next_);
        pos->next_ = new_node;
        std::swap(pos->data_, new_node->data_);
    }
    return true;
}

//bool PushFront(const T &data);
//bool PushFront(T &&data);
//bool PushBack(const T &data);
//bool PushBack(T &&data);

template <typename T>
std::ostream &operator<<(std::ostream &os, const SLinkedList<T> &link) {
    auto node = link.head_->next_;
    while (node) {
        os << node->data_ << "->";
        node = node->next_;
    }
    os << "nil";
    return os;
}

#endif  // __SINGLY_LINKED_LIST_H__
