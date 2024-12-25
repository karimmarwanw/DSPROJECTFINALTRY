#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include "Graph.h"
#include "HashTable.h"
#include "User.h"
#include "PriorityQueue.h"

class Functions {
private:
    static int nextID; // static counter for assigning unique IDs
    Graph userGraph;   // adjacency structure
    HashTable usersTable;  // (username -> User)

public:
    // Build a graph with `maxUsers` slots
    // Also set the usersTable to have capacity = maxUsers
    Functions(int maxUsers)
        : userGraph(maxUsers), usersTable(maxUsers)
    {
    }

    // ----------- AUTH -----------
    void signUp() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;

        if (usersTable.contains(username)) {
            std::cout << "Error: Username already exists.\n";
            return;
        }

        std::cout << "Enter password: ";
        std::cin >> password;

        // Create user, assign unique ID
        User newUser(username, password);
        newUser.setID(nextID++);
        usersTable.insert(username, newUser);

        std::cout << "User signed up successfully.\n";
    }

    void signIn() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (usersTable.contains(username)) {
            User* user = usersTable.getUser(username);
            if (user && user->getPassword() == password) {
                std::cout << "User signed in successfully.\n";
            } else {
                std::cout << "Error: Invalid password.\n";
            }
        } else {
            std::cout << "Error: User does not exist.\n";
        }
    }

    void signOut() {
        std::cout << "User signed out successfully.\n";
    }

    // ----------- FRIENDS -----------
    // direct friend addition
    void addFriend() {
        std::string username, friendUsername;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter friend's username: ";
        std::cin >> friendUsername;

        if (username == friendUsername) {
            std::cout << "Error: Cannot add yourself as a friend.\n";
            return;
        }

        if (usersTable.contains(username) && usersTable.contains(friendUsername)) {
            User* u = usersTable.getUser(username);
            User* f = usersTable.getUser(friendUsername);
            if (!u || !f) {
                std::cout << "Error retrieving user objects.\n";
                return;
            }

            // If they are not already friends, do:
            if (!u->hasFriend(friendUsername)) {
                u->addFriend(friendUsername);
                f->addFriend(username);
            }

            std::cout << "Friend added successfully.\n";
        } else {
            std::cout << "Error: One or both users do not exist.\n";
        }
    }


    void removeFriend() {
        std::string username, friendUsername;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter friend's username: ";
        std::cin >> friendUsername;

        if (usersTable.contains(username) && usersTable.contains(friendUsername)) {
            User* u = usersTable.getUser(username);
            User* f = usersTable.getUser(friendUsername);
            if (!u || !f) {
                std::cout << "Error retrieving user.\n";
                return;
            }

            int userID   = u->getID();
            int friendID = f->getID();

            if (userID < 0 || userID >= userGraph.getV()
             || friendID < 0 || friendID >= userGraph.getV()) {
                std::cout << "Error: ID out of range.\n";
                return;
            }

            // update friend lists
            u->removeFriend(friendUsername);
            f->removeFriend(username);

            // update adjacency
            userGraph.removeEdge(userID, friendID);

            std::cout << "Friend removed successfully.\n";
        } else {
            std::cout << "Error: One or both users do not exist.\n";
        }
    }

    // ----------- REQUESTS -----------
    void sendRequest() {
        std::string username, friendUsername;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter friend's username: ";
        std::cin >> friendUsername;

        if (usersTable.contains(username) && usersTable.contains(friendUsername)) {
            User* friendUser = usersTable.getUser(friendUsername);
            if (friendUser) {
                friendUser->addRequest(username);
                std::cout << "Friend request sent.\n";
            }
        } else {
            std::cout << "Error: One or both users do not exist.\n";
        }
    }

    void acceptFriend() {
        std::string username, friendUsername;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter friend's username: ";
        std::cin >> friendUsername;

        if (usersTable.contains(username) && usersTable.contains(friendUsername)) {
            User* user       = usersTable.getUser(username);
            User* friendUser = usersTable.getUser(friendUsername);
            if (user && friendUser && user->hasRequest(friendUsername)) {
                // update user objects
                user->addFriend(friendUsername);
                friendUser->addFriend(username);
                user->removeRequest(friendUsername);

                // update graph
                int uID = user->getID();
                int fID = friendUser->getID();
                if (uID >= 0 && uID < userGraph.getV() &&
                    fID >= 0 && fID < userGraph.getV())
                {
                    userGraph.addEdge(uID, fID);
                }

                std::cout << "Friend request accepted.\n";
            } else {
                std::cout << "Error: No friend request from this user.\n";
            }
        } else {
            std::cout << "Error: One or both users do not exist.\n";
        }
    }

    void rejectFriend() {
        std::string username, friendUsername;
        std::cout << "Enter your username: ";
        std::cin >> username;
        std::cout << "Enter friend's username: ";
        std::cin >> friendUsername;

        if (usersTable.contains(username) && usersTable.contains(friendUsername)) {
            User* user = usersTable.getUser(username);
            if (user && user->hasRequest(friendUsername)) {
                user->removeRequest(friendUsername);
                std::cout << "Friend request rejected.\n";
            } else {
                std::cout << "No friend request from this user.\n";
            }
        } else {
            std::cout << "One or both users do not exist.\n";
        }
    }

    void viewFriends() {
        std::string username;
        std::cout << "Enter your username: ";
        std::cin >> username;

        if (usersTable.contains(username)) {
            User* user = usersTable.getUser(username);
            if (user) {
                std::cout << "Friends of " << username << ":\n";
                user->printFriends();
            }
        } else {
            std::cout << "User does not exist.\n";
        }
    }

    int countMutualFriends(const std::string& nameA, const std::string& nameB) {
        if (!usersTable.contains(nameA) || !usersTable.contains(nameB)) return 0;

        User* userA = usersTable.getUser(nameA);
        User* userB = usersTable.getUser(nameB);
        if (!userA || !userB) return 0;

        int count = 0;
        for (User::Node* fA = userA->friends; fA; fA = fA->next) {
            for (User::Node* fB = userB->friends; fB; fB = fB->next) {
                if (fA->value == fB->value) {
                    count++;
                    break;
                }
            }
        }
        return count;
    }


    // ----------- RECOMMEND -----------
    void recommendFriends() {
        std::string username;
        std::cout << "Enter your username: ";
        std::cin >> username;

        // 1) Check if user exists
        if (!usersTable.contains(username)) {
            std::cout << "Error: User does not exist.\n";
            return;
        }

        User* currentUser = usersTable.getUser(username);
        if (!currentUser) {
            std::cout << "Error retrieving user data.\n";
            return;
        }

        // We'll use the same PriorityQueue as before
        PriorityQueue<std::pair<int, std::string>> pq;

        // 2) Iterate over all real users in usersTable
        for (auto it = usersTable.begin(); it != usersTable.end(); ++it) {
            const std::string& potentialName = (*it)->value.getUsername();

            // (a) Skip if it's me
            if (potentialName == username) {
                continue;
            }
            // (b) Skip if I'm already friends with them
            if (currentUser->hasFriend(potentialName)) {
                continue;
            }
            // (c) We can skip "dummy" if that might appear
            if (potentialName == "dummy") {
                continue;
            }

            // 3) Count mutual friends by *linked list intersection*
            int mutualCount = countMutualFriends(username, potentialName);

            // (d) Skip if zero mutual
            if (mutualCount == 0) {
                continue;
            }

            // 4) Push into the priority queue (descending priority = mutualCount)
            pq.push({mutualCount, potentialName}, mutualCount);
        }

        // 5) Output from highest mutual friend count to lowest
        std::cout << "\nRecommended friends for " << username << ":\n";
        while (!pq.empty()) {
            auto [count, friendName] = pq.top();
            pq.pop();
            std::cout << friendName << " (" << count << " mutual friends)\n";
        }
    }

};

// We define the static member outside the class
int Functions::nextID = 0;

#endif // FUNCTIONS_H
