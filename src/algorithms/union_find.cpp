#include "algorithms/union_find.h"

namespace algo {
    UnionFind::UnionFind(size_t n)
            : elem{new size_t[n]}, sz{n}, trees{new size_t[n]} {

        for (size_t i = 0; i < n; ++i) {
            elem[i] = i;
            trees[i] = 1;
        }
    }

    UnionFind::~UnionFind() {
        delete[] elem;
        delete[] trees;
    }

    inline size_t UnionFind::size() const {
        return sz;
    }

    bool UnionFind::find(size_t a, size_t b) {
        if (!valid(a) || !valid(b)) throw std::invalid_argument("index not in range");

        return root(a) == root(b);
    }

    void UnionFind::unite(size_t a, size_t b) {
        if (!valid(a) || !valid(b)) throw std::invalid_argument("index not in range");

        int i = root(a), j = root(b);
        if (i == j) return;

        if (trees[i] < trees[j]) {
            elem[i] = j;
            trees[j] += trees[i];
        } else {
            elem[j] = i;
            trees[i] += trees[j];
        }
    }

    inline bool UnionFind::valid(size_t a) const {
        return a < sz;
    }

    size_t UnionFind::root(size_t i) {
        while (i != elem[i]) {
            elem[i] = elem[elem[i]];
            i = elem[i];
        }
        return i;
    }

}