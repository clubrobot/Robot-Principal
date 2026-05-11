//
// Created by awing on 11/05/2026.
//

#ifndef SIMPLE_QUEUE_H
#define SIMPLE_QUEUE_H

#include <cstdio>

template <typename T, int MaxSize>
class SimpleQueue {
public:
    SimpleQueue() : head_(0), tail_(0), count_(0) {}

    bool push(const T &value) {
        if (count_ >= MaxSize) {
            printf("ERROR: SimpleQueue overflow\n");
            return false;
        }
        data_[tail_] = value;
        tail_ = (tail_ + 1) % MaxSize;
        ++count_;
        return true;
    }

    void pop() {
        if (count_ == 0) {
            printf("ERROR: SimpleQueue underflow\n");
            return;
        }
        head_ = (head_ + 1) % MaxSize;
        --count_;
    }

    T &front() { return data_[head_]; }
    const T &front() const { return data_[head_]; }

    [[nodiscard]] int size() const { return count_; }
    [[nodiscard]] bool empty() const { return count_ == 0; }

private:
    T data_[MaxSize];
    int head_;
    int tail_;
    int count_;
};

#endif //SIMPLE_QUEUE_H

