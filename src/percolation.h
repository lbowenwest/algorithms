#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

#include "union_find.h"

using std::size_t;
using coord = std::pair<size_t, size_t>;

class percolation {
  private:
    size_t sz;
    size_t len;
    bool* id;
    UnionFindQUW uf;

    inline size_t index(size_t r, size_t c) {return sz * r + c; };
    inline size_t index(coord c) {return sz * c.first + c.second; };

    inline bool valid(size_t i) {return i < sz; };
    inline bool valid(size_t r, size_t c) {return r < sz && c < sz; };
    inline bool valid(coord c) {return c.first < sz && c.second < sz; };

    void connect_adjacents(size_t r, size_t c);
    std::vector<coord> neighbours(size_t r, size_t c);

    std::vector<coord> row(size_t r);
    std::vector<coord> column(size_t c);

  public:
    percolation(size_t n);    
    ~percolation() {delete [] id; };

    void open(size_t r, size_t c);
    void open(coord c);
    bool is_open(size_t r, size_t c);
    bool is_open(coord c);
    bool check();

    std::vector<coord> points();
    int size() {return sz;};
    int open_count() {return 1; };
    void print();
};

percolation generate_from_file(std::fstream& f);

