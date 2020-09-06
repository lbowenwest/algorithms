#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

#include "union_find.h"

using std::size_t;

namespace algo {

    class percolation {
    public:
        struct coord {
            std::size_t x, y;
        };

    private:
        size_t sz;
        size_t len;
        bool *id;
        algo::UnionFind uf;

        inline size_t index(size_t r, size_t c) const;

        inline size_t index(coord c) const;

        inline bool valid(size_t i) const;

        inline bool valid(size_t r, size_t c) const;

        inline bool valid(coord c) const;

        void connect_adjacents(size_t r, size_t c);

        std::vector<coord> neighbours(size_t r, size_t c);

        std::vector<coord> row(size_t r);

        std::vector<coord> column(size_t c);

    public:
        explicit percolation(size_t n);

        ~percolation() { delete[] id; };

        static percolation generate_from_file(std::fstream &f);

        void open(size_t r, size_t c);

        void open(coord c);

        bool is_open(size_t r, size_t c);

        bool is_open(coord c);

        bool check();

        std::vector<coord> points();

        size_t size() const { return sz; };

        int open_count() { return 1; };
    };


}

