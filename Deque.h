#ifndef DEQUE_H
#define DEQUE_H

#include "List.h"

template <typename T>
class Deque {
private:
    List<T> data;

public:
    using iterator       = typename List<T>::iterator;
    using const_iterator = typename List<T>::const_iterator;

    void push_back(const T& value) {
        data.push_back(value);
    }

    void pop_front() {
        data.pop_front();
    }

    T& front() {
        return data.front();
    }

    T& back() {
        return data.back();
    }

    void erase(int index) {
        data.erase(index);
    }

    T& operator[](int index) {
        return data[index];
    }

    const T& operator[](int index) const {
        return data[index];
    }

    int size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    void clear() {
        data.clear();
    }

    iterator begin() {
        return data.begin();
    }
    iterator end() {
        return data.end();
    }

    const_iterator begin() const {
        return data.begin();
    }
    const_iterator end() const {
        return data.end();
    }
};

#endif // DEQUE_H
