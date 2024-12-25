#ifndef LIST_H
#define LIST_H

#include <stdexcept>

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    List() : head(nullptr), tail(nullptr), count(0) {}

    ~List() {
        clear();
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        } else {
            head = tail = newNode;
        }
        ++count;
    }

    void pop_front() {
        if (head) {
            Node* temp = head;
            head = head->next;
            if (head) {
                head->prev = nullptr;
            } else {
                tail = nullptr;
            }
            delete temp;
            --count;
        }
    }

    T& front() {
        if (!head) {
            throw std::out_of_range("List is empty");
        }
        return head->data;
    }

    T& back() {
        if (!tail) {
            throw std::out_of_range("List is empty");
        }
        return tail->data;
    }

    void erase(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        if (current->prev) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        delete current;
        --count;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    int size() const {
        return count;
    }

    bool empty() const {
        return (count == 0);
    }

    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        count = 0;
    }

    // ---- Iterators ----
    class iterator {
    private:
        Node* ptr;
    public:
        iterator(Node* ptr) : ptr(ptr) {}
        iterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }
        bool operator!=(const iterator& other) const {
            return ptr != other.ptr;
        }
        T& operator*() {
            return ptr->data;
        }
    };

    iterator begin() { return iterator(head); }
    iterator end()   { return iterator(nullptr); }

    class const_iterator {
    private:
        const Node* ptr;
    public:
        const_iterator(const Node* ptr) : ptr(ptr) {}
        const_iterator& operator++() {
            if (ptr) ptr = ptr->next;
            return *this;
        }
        bool operator!=(const const_iterator& other) const {
            return ptr != other.ptr;
        }
        const T& operator*() const {
            return ptr->data;
        }
    };

    const_iterator begin() const { return const_iterator(head); }
    const_iterator end()   const { return const_iterator(nullptr); }
};

#endif // LIST_H
