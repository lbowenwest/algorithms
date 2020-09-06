#pragma once

#include <stdexcept>
#include <utility>

namespace algo {
    class UnionFind {
    public:
        explicit UnionFind(std::size_t n);
        ~UnionFind();

        std::size_t size() const;
        bool find(std::size_t a, std::size_t b);
        void unite(std::size_t a, std::size_t b);

    private:
        std::size_t* elem;
        std::size_t sz;
        std::size_t* trees;

        bool valid(std::size_t a) const;
        std::size_t root(std::size_t i);
    };

}


