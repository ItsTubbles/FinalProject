//DisjointSet.h
#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>

using namespace std;

struct DisjointSet {
    vector<int> parent;
    vector<int> size;

    DisjointSet(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    //retruns the parent node
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    //unions two sets
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (size[rootX] < size[rootY]) swap(rootX, rootY);
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }

    //retuns the size aka the depth of the set
    int getSize(int x) {
        return size[find(x)];
    }
};

#endif //DISJOINTSET_H