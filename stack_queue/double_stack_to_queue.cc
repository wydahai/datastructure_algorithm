/**
 * 题目：用两个栈实现队列
 * 描述：用两个栈来实现一个队列，完成队列的Push和Pop操作。 
 *       队列中的元素为int类型。
 * 解答：入队时每次都压入到第一个栈
 *       出队时，如果第二个栈不为空，则直接从第二个栈中弹出栈顶元素即可；
 *       若为空，则依次将第一个栈中到数据压入到第二个栈中，最后弹出栈顶
 *       元素即可
 *       为什么出队后不需要将第二个栈中的数据再放回第一个栈中，而是在下
 *       一次出队时直接操作第二个栈的顶端？因为第二个栈中的顶端就是最先
 *       入栈的元素
 */

#include <iostream>
#include <stack>
#include <exception>


template <typename T>
class Queue {
private:
    std::stack<T> first_;
    std::stack<T> second_;

public:
    inline void Push(const T &data);
    T Pop();

    bool Empty() const { return first_.empty() && second_.empty(); }
};

template <typename T>
void Queue<T>::Push(const T &data) {
    // 入队时直接压到first_队列中即可
    first_.push(data);
}

template <typename T>
T Queue<T>::Pop() {
    if (second_.empty()) {  // 如果第二个栈为空，则将first_中所有数据压入
        while (!first_.empty()) {
            second_.push(first_.top());
            first_.pop();
        }
    }
    if (!second_.empty()) {
        auto data = second_.top();
        second_.pop();
        return data;
    }
    // warning
}


int main() {
    Queue<int> queue;
    for (int num=0; num<10; ++num) {
        queue.Push(num);
    }

    while (!queue.Empty()) {
        std::cout << queue.Pop() << std::endl;
    }

    return 0;
}
