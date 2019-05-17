#ifndef __SORT_BASE_H__
#define __SORT_BASE_H__

#include <cassert>
#include <iostream>

constexpr int MAX_SIZE = 32;

struct List {
    int data_[MAX_SIZE];
    int length_;
};

void SwapElem(List *ls, int i, int j) {
    assert(ls && i>=0 && i<MAX_SIZE && j>=0 && j<MAX_SIZE);

    ls->data_[i] ^= ls->data_[j];
    ls->data_[j] ^= ls->data_[i];
    ls->data_[i] ^= ls->data_[j];
}

void PrintList(const List *ls) {
    assert(ls);
    for (int idx=0; idx<ls->length_; ++idx) {
        std::cout << ls->data_[idx] << ' ';
    }
    std::cout << std::endl;
}

#endif  // __SORT_BASE_H__
