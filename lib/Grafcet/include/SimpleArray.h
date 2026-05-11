//
// Created by awing on 11/05/2026.
//

#ifndef SIMPLE_ARRAY_H
#define SIMPLE_ARRAY_H

#include <cstdio>

template <typename T, int MaxSize>
class SimpleArray {
public:
    SimpleArray() : size_(0) {}

    bool push_back(const T &value) {
        if (size_ >= MaxSize) {
            printf("ERROR: SimpleArray overflow\n");
            return false;
        }
        data_[size_] = value;
        ++size_;
        return true;
    }

    [[nodiscard]] int size() const { return size_; }
    [[nodiscard]] bool empty() const { return size_ == 0; }

    T &operator[](int index) { return data_[index]; }
    const T &operator[](int index) const { return data_[index]; }

    T &front() { return data_[0]; }
    const T &front() const { return data_[0]; }

    T *begin() { return data_; }
    const T *begin() const { return data_; }
    T *end() { return data_ + size_; }
    const T *end() const { return data_ + size_; }

private:
    T data_[MaxSize];
    int size_;
};

#endif //SIMPLE_ARRAY_H

