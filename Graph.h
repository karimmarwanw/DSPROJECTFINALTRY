#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
#include <stdexcept>
#include "HashTable.h"

using namespace std;

class Graph {
private:
    int numUsers;   // Number of "slots" for users
    HashTable* adj; // adjacency array: each index is a HashTable (storing edges)

    void DFSUtil(int u, bool visited[]) {
        visited[u] = true;
        for (int i = 0; i < adj[u].capacity; i++) {
            HashTable::Node* node = adj[u].table[i];
            while (node) {
                int neighbor = stoi(node->key);
                if (!visited[neighbor]) {
                    DFSUtil(neighbor, visited);
                }
                node = node->next;
            }
        }
    }

public:
    Graph(int numUsers) : numUsers(numUsers) {
        adj = new HashTable[numUsers];
        for (int i = 0; i < numUsers; i++) {
            adj[i] = HashTable(numUsers);
        }
    }

    ~Graph() {
        delete[] adj;
    }

    int getNumUsers() const {
        return numUsers;
    }

    // Add an undirected edge between u and v
    void addEdge(int u, int v) {
        if (u < 0 || u >= numUsers || v < 0 || v >= numUsers) {
            throw out_of_range("Invalid user ID in addEdge()");
        }
    }

    void removeEdge(int u, int v) {
        if (u < 0 || u >= numUsers || v < 0 || v >= numUsers) {
            return;
        }
        adj[u].remove(to_string(v));
        adj[v].remove(to_string(u));
    }

    bool areConnected(int u, int v) const {
        if (u < 0 || u >= numUsers || v < 0 || v >= numUsers) {
            return false;
        }
        return adj[u].contains(to_string(v));
    }

};

#endif // GRAPH_H

