/**
 * 小顶堆示例
 * 二叉堆实现了优先级队列接口
 * 插入与删除的时间复杂度是O(logn) 
 */

#ifndef __ALGORITHM_BINARY_HEAP_H__
#define __ALGORITHM_BINARY_HEAP_H__

#include <algorithm>
#include <iostream>
#include <cassert>

#include "array.h"


template<class T>
class MinBinaryHeap {
private:
    Array<T> array_;
    size_t length_;  // 堆大小，使用无符号递减操作时容易越界

public:
    /**
     * 构建一个空堆：堆大小为0，array_为1
     */
    explicit MinBinaryHeap();
    /**
     * 通过_array构建一个堆，需要进行调整，满足堆堆特性
     */
    explicit MinBinaryHeap(const Array<T> &_array);
    ~MinBinaryHeap() {}

public:
    bool Insert(const T &elem);
    bool Insert(T &&elem);

    T&& Delete();

    size_t Size() const {
        return length_;
    }

    const T& Min() const {
        assert(length_ > 0);
        return array_[0];
    }

    /**
     * 对于小顶堆更适合降序排序，因为是从堆顶开始，堆顶是最小元素
     * 大顶堆的堆顶是最大值，从堆顶开始，便于进行升序排序
     */
    void SortByDesc();
    /**
     * 此处不能简单的进行反转，因为array_的实际长度可能大于
     * 堆的长度length_(堆每次Resize按照指数级增长)
     * void SortByAsc() {
     *     array_.Reverse();
     * }
     */

private:
    static ssize_t LeftChildIndex(size_t parent) {
        return 2 * parent + 1;
    }

    static ssize_t RightChildIndex(size_t parent) {
        return 2 * parent + 2;
    }

    static ssize_t ParentIndex(size_t child) {
        return (child - 1) / 2;  // NOTE: child must greater than 1
    }

    void Resize();
    void BubbleUp(size_t idx);
    void TrikleDown(size_t idx);

    template<class T1>
    friend std::ostream& operator<<(std::ostream &out, 
                                    const MinBinaryHeap<T1> &heap);
};

template<class T>
MinBinaryHeap<T>::MinBinaryHeap() : array_{1}, length_{0} {
}

template<class T>
MinBinaryHeap<T>::MinBinaryHeap(const Array<T> &_array) 
    : array_{_array}, length_{_array.Length()} {
    // 根据已有序列构建堆时时向下渗透
    for (ssize_t idx=length_/2-1; idx>=0; --idx) {
        TrikleDown(idx);
    }
}

template<class T>
void MinBinaryHeap<T>::Resize() {
    Array<T> temp{std::max(2*length_, (size_t)1)};
    /**
     * Array<T>重载了operator+方法，返回一个指针，此处的+0
     * 是必不可少的，这样才会返回指针
     */
    std::copy(array_+0, array_+length_, temp+0);
    array_ = std::move(temp);
}

/**
 * 向上调整-idx是开始调整的索引
 */
template<class T>
void MinBinaryHeap<T>::BubbleUp(size_t child) {
    size_t parent = ParentIndex(child);
    while (child>0 && array_[child]<array_[parent]) {
        std::swap(array_[child], array_[parent]);
        child = parent;
        parent = ParentIndex(child);
    }
}

/**
 * 小顶堆插入操作：
 * 向堆中插入一个元素时，在堆的尾部插入该新元素，然后向上进行调整
 * （交换新元素与parent元素）直到新元素的值不小于其parent（另外表
 * 述：新元素大于等于parent时停止调整）
 */
template<class T>
bool MinBinaryHeap<T>::Insert(const T &elem) {
    if ((length_ + 1) > array_.Length()) {  // 如果堆已满进行扩容
        Resize();
    }
    array_[length_++] = elem;
    BubbleUp(length_-1);  // 向上调整新插入的元素
    return true;
}

template<class T>
bool MinBinaryHeap<T>::Insert(T &&elem) {
    if ((length_ + 1) > array_.Length()) {  // 如果堆已满进行扩容
        Resize();
    }
    array_[length_++] = std::move(elem);
    BubbleUp(length_-1);  // 向上调整新插入的元素
    return true;
}

/**
 * 删除：就是删除堆顶元素，一般做法是交换堆顶（index=0）和最后一个
 * 元素（index=length-1），然后从堆顶位置开始向下调整
 */
template<class T>
T&& MinBinaryHeap<T>::Delete() {
    assert(length_ > 0);
#if 0
    /**
     * 此处代码有问题：因为会调用Resize，所以内存可能已经改变，
     * 不能直接返回删除前的最后一个元素
     */
    std::swap(array_[0], array_[--length_]);
    TrikleDown(0);
    if (3*length_ < array_.Length()) {
        Resize();
    }
    return std::move((array_[length_]);
#endif
    T ret = std::move(array_[0]);
    array_[0] = std::move(array_[--length_]);
    TrikleDown(0);
    if (3*length_ < array_.Length()) {
        Resize();
    }
    return std::move(ret);
}

template<class T>
void MinBinaryHeap<T>::TrikleDown(size_t parent) {
    T parentValue = std::move(array_[parent]);
    size_t child = LeftChildIndex(parent);
    while (child < length_) {
        // 先选择出较小的孩子节点
        size_t rchild = RightChildIndex(parent);
        if (rchild<length_ && array_[rchild]<array_[child]) {
            child = rchild;
        }
        if (parentValue > array_[child]) {
            array_[parent] = std::move(array_[child]);
            parent = child;
            child = LeftChildIndex(parent);
        } else {
            break;
        }
    }
    array_[parent] = std::move(parentValue);
}

/**
 * 基本思想：交换堆顶和尾部元素，此时尾部元素是最小的值，然后从
 * 堆顶开始向下调整，再交换调整后的堆顶和尾部元素（原来的堆顶元
 * 素再交换后不再属于堆
 */
template<class T>
void MinBinaryHeap<T>::SortByDesc() {
    size_t reserveLen = length_;
    while (--length_ > 0) {
        std::swap(array_[0], array_[length_]);
        TrikleDown(0);
    }
    length_ = reserveLen;
}

template<class T>
std::ostream& operator<<(std::ostream &out, 
                         const MinBinaryHeap<T> &heap) {
    for (size_t idx=0; idx!=heap.length_; ++idx) {
        out << heap.array_[idx] << ' ';
    }
    return out;
}

#endif
