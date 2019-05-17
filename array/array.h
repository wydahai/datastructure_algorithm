#ifndef __ALGORITHM_ARRAY_H__
#define __ALGORITHM_ARRAY_H__

#include <iostream>
#include <algorithm>
#include <cassert>
#include <initializer_list>


template<class T> class Array;
template<class T>
std::ostream& operator<<(std::ostream &out, const Array<T> &arr);

/**
 * NOTE: C++11已经提供了容器: array
 */
template<class T>
class Array {
private:
    T *ptr = nullptr;
    size_t len_ = 0;

public:
    explicit Array(size_t len) : ptr{new T[len]}, len_{len} {}
    explicit Array(size_t len, const T &init) : Array{len} {
        for (size_t idx=0; idx!=len_; ++idx) {
            ptr[idx] = init;
        }
    }

    ~Array() {
        delete[] ptr;
    }

    Array(const Array &oth);
    Array& operator=(const Array &oth);

    Array(Array &&oth);
    Array& operator=(Array &&oth);

    size_t Length() const {
        return len_;
    }

    T& operator[](size_t idx) {
        return const_cast<T&>(static_cast<const Array&>(*this)[idx]);
    }

    const T& operator[](size_t idx) const {
        assert(idx < len_);
        return *(ptr + idx);
    }

    T* operator+(size_t idx) {
         return const_cast<T*>(static_cast<const Array&>(*this) + idx);
    }

    const T* operator+(size_t idx) const {
        return &ptr[idx];
    }

    void Swap(size_t i, size_t j) {
        std::swap(ptr[i], ptr[j]);
    }

    void Fill(const T &val) {
        std::fill(ptr, ptr+len_, val);
    }


    void Reverse() {
        for (size_t idx=0; idx<len_/2; ++idx) {
            Swap(idx, len_-idx-1);
        }
    }

    template<class T1>
    friend std::ostream& operator<<(std::ostream &out, const Array<T1> &arr);
};

template<class T>
Array<T>::Array(const Array<T> &oth) {
    ptr = new T[oth.len_];
    for (size_t idx=0; idx!=oth.len_; ++idx) {
        ptr[idx] = oth.ptr[idx];
    }
    len_= oth.len_;
}

template<class T>
Array<T>& Array<T>::operator=(const Array<T> &oth) {
    if (this == &oth) {
        return *this;
    }

    if (ptr) {
        delete ptr;
    }
    ptr = new T[oth.len_];
    for (size_t idx=0; idx!=oth.len_; ++idx) {
        ptr[idx] = oth.ptr[idx];
    }
    len_ = oth.len_;
    return *this;
}

template<class T>
Array<T>::Array(Array<T> &&oth) {
    ptr = oth.ptr;
    oth.ptr = nullptr;
    len_ = oth.len_;
    oth.len_ = 0;
}

template<class T>
Array<T>& Array<T>::operator=(Array<T> &&oth) {
    if (this == &oth) {
        return *this;
    }
    if (ptr) {
        delete[] ptr;
    }
    ptr = oth.ptr;
    oth.ptr = nullptr;
    len_ = oth.len_;
    oth.len_ = 0;
    return *this;
}

template<class T>
std::ostream& operator<<(std::ostream &out, const Array<T> &arr) {
    size_t idx = 0;
    while (idx != arr.len_) {
        out << *(arr.ptr + idx) << ' ';
        ++idx;
    }
    return out;
}

#endif  // __ALGORITHM_ARRAY_H__
