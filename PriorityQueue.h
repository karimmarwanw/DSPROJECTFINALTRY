#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class PriorityQueue {
private:
    struct Node {
        T data;
        int priority;
        Node* next;
        Node(const T& d, int p) : data(d), priority(p), next(nullptr) {}
    };
    Node* head;

    // Bubble sort so that head is max priority
    void bubbleSort() {
        if (!head) return;
        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current->next) {
                if (current->priority < current->next->priority) {
                    // Swap data + priority
                    T tempData = current->data;
                    int tempPr = current->priority;
                    current->data = current->next->data;
                    current->priority = current->next->priority;
                    current->next->data = tempData;
                    current->next->priority = tempPr;
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

public:
    PriorityQueue() : head(nullptr) {}

    ~PriorityQueue() {
        while (!empty()) {
            pop();
        }
    }

    bool empty() const {
        return (head == nullptr);
    }

    void push(const T& element, int priority) {
        Node* newNode = new Node(element, priority);
        // Insert at front
        newNode->next = head;
        head = newNode;
        // bubble sort
        bubbleSort();
    }

    T top() const {
        if (empty()) {
            throw runtime_error("PriorityQueue is empty");
        }
        return head->data;  // highest priority
    }

    void pop() {
        if (empty()) {
            throw runtime_error("PriorityQueue is empty");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }
};

#endif // PRIORITYQUEUE_H