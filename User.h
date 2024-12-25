#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

using namespace std;

class User {
private:
    int userID;  // A unique integer ID for each user

public:
    string username;
    string password;

    struct Node {
        string value;
        Node* next;
        Node(const string& value) : value(value), next(nullptr) {}
    };

    Node* friends;
    Node* requests;
    Node* pending;

    User(const string& user = "", const string& pass = "")
        : userID(-1), username(user), password(pass),
          friends(nullptr), requests(nullptr), pending(nullptr)
    {
    }

    ~User() {
        // Clean up all three lists
        while (friends) {
            Node* temp = friends;
            friends = friends->next;
            delete temp;
        }
        while (requests) {
            Node* temp = requests;
            requests = requests->next;
            delete temp;
        }
        while (pending) {
            Node* temp = pending;
            pending = pending->next;
            delete temp;
        }
    }

    //----------- ID Management -----------
    void setID(int id) { userID = id; }
    int getID() const  { return userID; }

    //----------- Linked-list helpers -----------
    void insert(Node*& head, const string& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void remove(Node*& head, const string& value) {
        Node* temp = head;
        Node* prev = nullptr;
        while (temp != nullptr && temp->value != value) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) return; // not found
        if (prev == nullptr) {
            head = head->next;
        } else {
            prev->next = temp->next;
        }
        delete temp;
    }

    bool contains(Node* head, const string& value) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->value == value) return true;
            temp = temp->next;
        }
        return false;
    }

    void print(Node* head) const {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->value << endl;
            temp = temp->next;
        }
    }

    //----------- Friends, Requests, Pending -----------
    void addFriend(const string& friendName) {
        insert(friends, friendName);
    }
    void removeFriend(const string& friendName) {
        remove(friends, friendName);
    }
    bool hasFriend(const string& friendName) const {
        return contains(friends, friendName);
    }

    void addRequest(const string& requestName) {
        insert(requests, requestName);
    }
    void removeRequest(const string& requestName) {
        remove(requests, requestName);
    }
    bool hasRequest(const string& requestName) const {
        return contains(requests, requestName);
    }

    void addPending(const string& pendingName) {
        insert(pending, pendingName);
    }
    void removePending(const string& pendingName) {
        remove(pending, pendingName);
    }
    bool hasPending(const string& pendingName) const {
        return contains(pending, pendingName);
    }

    void printFriends() const {
        print(friends);
    }
    void printRequests() const {
        print(requests);
    }
    void printPending() const {
        print(pending);
    }

    //----------- Basic Getters -----------
    string getUsername() const {
        return username;
    }
    string getPassword() const {
        return password;
    }
};

#endif // USER_H