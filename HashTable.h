#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include "User.h"

using namespace std;

class HashTable {
public:
    struct Node {
        string key;
        User value;
        Node* next;

        Node(const string& k, const User& val)
            : key(k), value(val), next(nullptr) {}
    };

    Node** table;   // pointer to an array of Node* (the buckets)
    int capacity;   // total number of buckets

    // Default constructor: sets capacity = 10
    HashTable() {
        capacity = 10;
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    // Constructor that lets you specify capacity
    HashTable(int cap) : capacity(cap) {
        table = new Node*[capacity];
        for (int i = 0; i < capacity; i++) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    // A simple string-hash
    int hash(const string& key) const {
        unsigned long hashVal = 0;
        for (char c : key) {
            hashVal = (hashVal << 5) + c;  // same as hashVal * 32 + c
        }
        return hashVal % capacity;
    }

    // Insert a key/value pair into the table
    void insert(const string& key, const User& value) {
        int index = hash(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Check if the table contains a given key
    bool contains(const string& key) const {
        int index = hash(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Retrieve a pointer to the User object, if it exists
    User* getUser(const string& key) {
        int index = hash(key);
        Node* current = table[index];
        while (current) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr; // not found
    }

    // Remove a key from the table
    bool remove(const string& key) {
        int index = hash(key);
        Node* current = table[index];
        Node* prev = nullptr;
        while (current) {
            if (current->key == key) {
                if (!prev) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false; // not found
    }

    // A simple iterator for all key/value pairs in the table
    class Iterator {
    private:
        const HashTable* tablePtr;
        int bucketIndex;
        Node* nodePtr;
    public:
        Iterator(const HashTable* t, int b, Node* n)
            : tablePtr(t), bucketIndex(b), nodePtr(n) {}

        bool operator!=(const Iterator& other) const {
            return (tablePtr != other.tablePtr
                 || bucketIndex != other.bucketIndex
                 || nodePtr != other.nodePtr);
        }

        // prefix ++
        Iterator& operator++() {
            if (!nodePtr) return *this;
            nodePtr = nodePtr->next;
            while (!nodePtr) {
                bucketIndex++;
                if (bucketIndex >= tablePtr->capacity) {
                    break;
                }
                nodePtr = tablePtr->table[bucketIndex];
            }
            return *this;
        }

        Node* operator*() const {
            return nodePtr;
        }
    };

    Iterator begin() const {
        int b = 0;
        Node* n = nullptr;
        while (b < capacity && table[b] == nullptr) {
            b++;
        }
        if (b < capacity) {
            n = table[b];
        }
        return Iterator(this, b, n);
    }

    Iterator end() const {
        return Iterator(this, capacity, nullptr);
    }
};

#endif // HASHTABLE_H