#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <utility>
#include <stdexcept>
#include <new>

template <typename KeyType, typename ValueType>
class Map {
private:
    std::pair<KeyType, ValueType>* data;
    int myCapacity;
    int mySize;

public:
    Map(int numElements = 1000)
        : myCapacity(numElements), mySize(0)
    {
        data = new(std::nothrow) std::pair<KeyType, ValueType>[myCapacity];
        if (!data) {
            throw std::bad_alloc();
        }
    }

    ~Map() {
        delete[] data;
    }

    void insert(const KeyType& key, const ValueType& value) {
        // Overwrite if key already exists
        for (int i = 0; i < mySize; i++) {
            if (data[i].first == key) {
                data[i].second = value;
                return;
            }
        }
        // Otherwise, add new entry
        if (mySize < myCapacity) {
            data[mySize].first  = key;
            data[mySize].second = value;
            mySize++;
        } else {
            throw std::out_of_range("Map capacity exceeded");
        }
    }

    bool contains(const KeyType& key) const {
        for (int i = 0; i < mySize; i++) {
            if (data[i].first == key) {
                return true;
            }
        }
        return false;
    }

    ValueType& operator[](const KeyType& key) {
        for (int i = 0; i < mySize; i++) {
            if (data[i].first == key) {
                return data[i].second;
            }
        }
        if (mySize < myCapacity) {
            data[mySize].first  = key;
            data[mySize].second = ValueType{};
            mySize++;
            return data[mySize - 1].second;
        }
        throw std::out_of_range("Map capacity exceeded");
    }

    void erase(const KeyType& key) {
        for (int i = 0; i < mySize; i++) {
            if (data[i].first == key) {
                // Shift everything left
                for (int j = i; j < mySize - 1; j++) {
                    data[j] = data[j + 1];
                }
                mySize--;
                return;
            }
        }
        throw std::out_of_range("Key not found");
    }

    std::pair<KeyType, ValueType>* begin() {
        return data;
    }

    std::pair<KeyType, ValueType>* end() {
        return data + mySize;
    }

    int size() const {
        return mySize;
    }

    void display(std::ostream& out) const {
        if (mySize == 0) {
            out << "Map is empty!" << std::endl;
            return;
        }
        for (int i = 0; i < mySize; i++) {
            out << "[key: " << data[i].first
                << ", value: " << data[i].second << "] ";
        }
        out << std::endl;
    }
};

template <typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream& out, const Map<KeyType, ValueType>& aList) {
    aList.display(out);
    return out;
}

#endif // MAP_H
