/**
 * 题目：使用两个队列实现一个栈。
 */

#include <iostream>
#include <queue>
#include <exception>


template <typename T>
class Stack {
private:
    std::queue<T> first_;
    std::queue<T> second_;

public:
    void Push(const T &data);
    T Top();

    bool Empty() const { return (first_.empty() && second_.empty()); }
};


template <typename T>
void Stack<T>::Push(const T &data) {
    // 不知道此时哪个队列为空哪个不为空，如果都为空则压入到哪个队列
    // 都可以，如果有一个不为空，则需要压入到不为空到队列，不可能两
    // 个队列同时都不为空，因为弹出时会把不为空的所有数据入队到为空
    // 的队列中
    if (!first_.empty()) {
        first_.push(data);
    } else {
        second_.push(data);
    }
}

template <typename T>
T Stack<T>::Top() {
    if (first_.empty() && second_.empty()) {
        //std::throw();
    }

    if (!first_.empty()) {  // 将数据都入队到second_
        while (first_.size() > 1) {  // 需要保留一个用来进行弹出
            second_.push(first_.front());
            first_.pop();
        }
        auto data = first_.front();
        first_.pop();
        return data;
    } else {
        while (second_.size() > 1) {
            first_.push(second_.front());
            second_.pop();
        }
        auto data = second_.front();
        second_.pop();
        return data;
    }
}


int main() {
    Stack<int> st;
    for (int num=0; num<10; ++num) {
        st.Push(num);
    }
    while (!st.Empty()) {
        std::cout << st.Top() << std::endl;
    }

    return 0;
}
