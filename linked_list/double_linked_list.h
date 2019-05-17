#ifndef __DOUBLE_LINKED_LIST_H__
#define __DOUBLE_LINKED_LIST_H__

#include <memory>

template <typename T>
struct DLListNode {
    T data_{};
    std::shared_ptr<DLListNode>
};

#endif
