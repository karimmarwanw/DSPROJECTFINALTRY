#pragma once
#include <iostream>
#include <stdexcept>
#include "List.h"

template <typename T>
class UnorderedSet {
private:
    List<T> data; // List to store the elements

public:
    UnorderedSet() {}

    void insert(const T& value);
    void remove(const T& value);
    bool contains(const T& value) const;
    bool empty() const { return data.empty(); }
    int size() const { return data.size(); }
    void clear() { data.clear(); }
    void display(std::ostream& out) const;

    using iterator       = typename List<T>::iterator;
    using const_iterator = typename List<T>::const_iterator;

    iterator begin() { return data.begin(); }
    iterator end()   { return data.end(); }

    const_iterator begin() const { return data.begin(); }
    const_iterator end()   const { return data.end(); }

    friend std::ostream& operator<<(std::ostream& out, const UnorderedSet& set) {
        set.display(out);
        return out;
    }
};

template <typename T>
void UnorderedSet<T>::insert(const T& value) {
    if (!contains(value)) {
        data.push_back(value);
    }
}

template <typename T>
void UnorderedSet<T>::remove(const T& value) {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] == value) {
            data.erase(i);
            return;
        }
    }
    throw std::out_of_range("Value not found");
}

template <typename T>
bool UnorderedSet<T>::contains(const T& value) const {
    for (int i = 0; i < data.size(); ++i) {
        if (data[i] == value) {
            return true;
        }
    }
    return false;
}

template <typename T>
void UnorderedSet<T>::display(std::ostream& out) const {
    if (data.empty()) {
        out << "Set is empty" << std::endl;
        return;
    }
    out << "{";
    for (int i = 0; i < data.size(); ++i) {
        out << data[i];
        if (i < data.size() - 1) {
            out << ", ";
        }
    }
    out << "}" << std::endl;
}
