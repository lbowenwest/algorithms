#include "algorithms/union_find.h"
#include "algorithms/percolation.h"

#include <array>

using std::size_t;
using std::vector;
using std::cout;


namespace algo {

    percolation::percolation(size_t n) : sz(n), len(n * n + 2), id(new bool[n * n]()),
                                         uf(algo::UnionFind((n * n) + 2)) {
        for (auto &i : row(0)) uf.unite(len - 2, index(i));
        for (auto &i : row(sz - 1)) uf.unite(len - 1, index(i));
    }


    void percolation::connect_adjacents(size_t r, size_t c) {
        if (!valid(r, c)) return;
        for (auto i : neighbours(r, c)) {
            if (is_open(i)) uf.unite(index(i), index(r, c));
        }
    }

    vector<percolation::coord> percolation::neighbours(size_t r, size_t c) {
        std::array<coord, 4> directions{{{r - 1, c}, {r + 1, c}, {r, c - 1}, {r, c + 1}}};
        vector<coord> res;
        for (const auto &dir: directions) {
            if (valid(dir.x, dir.y)) {
                res.emplace_back(dir);
            }
        }
        return res;
    }


    void percolation::open(size_t r, size_t c) {
        if (!valid(r, c)) throw std::invalid_argument("index not in range");
        id[index(r, c)] = true;
        connect_adjacents(r, c);
    }

    void percolation::open(coord c) {
        open(c.x, c.y);
    }

    bool percolation::is_open(coord c) {
        return is_open(c.x, c.y);
    }

    bool percolation::is_open(size_t r, size_t c) {
        if (!valid(r, c)) throw std::invalid_argument("index not in range");
        return id[index(r, c)];
    }

    vector<percolation::coord> percolation::row(size_t r) {
        if (!valid(r)) throw std::invalid_argument("index not in range");
        vector<coord> res(sz);
        for (unsigned i = 0; i < sz; ++i)
            res.push_back({r, i});
        return res;
    }

    vector<percolation::coord> percolation::column(size_t c) {
        if (!valid(c)) throw std::invalid_argument("index not in range");
        vector<coord> res(sz);
        for (size_t i = 0; i < sz; ++i) {
            res.push_back({i, c});
        }
        return res;
    }

    vector<percolation::coord> percolation::points() {
        vector<coord> res;
        for (size_t i = 0; i < sz; ++i) {
            auto r = row(i);
            res.insert(res.end(), std::make_move_iterator(r.begin()), std::make_move_iterator(r.end()));
        }
        return res;
    }


    bool percolation::check() {
        return uf.find(len - 2, len - 1);
    }


    percolation percolation::generate_from_file(std::fstream &f) {
        int size{0};
        vector<percolation::coord> sites;

        if (f.is_open()) {
            f >> size;
            size_t a, b;
            while (f >> a >> b)
                sites.push_back({--a, --b});
        }
        percolation pc(size);
        for (auto &c : sites) {
            pc.open(c);
        }

        return pc;
    }

    size_t percolation::index(percolation::coord c) const {
        return sz * c.x + c.y;
    }

    size_t percolation::index(size_t r, size_t c) const {
        return sz * r + c;
    }

    bool percolation::valid(size_t i) const {
        return i < sz;
    }

    bool percolation::valid(size_t r, size_t c) const {
        return r < sz && c < sz;
    }

    bool percolation::valid(percolation::coord c) const {
        return c.x < sz && c.y < sz;
    }

}