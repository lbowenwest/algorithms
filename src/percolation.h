#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>

#include "union_find.h"

using coord = std::pair<std::size_t,std::size_t>;

class percolation {
  private:
    unsigned sz;
    unsigned len;
    bool* id;
    UnionFindQUW uf;

    inline unsigned index(unsigned r, unsigned c) {return sz * r + c; };
    inline unsigned index(coord c) {return sz * c.first + c.second; };

    inline bool valid(unsigned i) {return i < sz; };
    inline bool valid(unsigned r, unsigned c) {return r < sz && c < sz; };
    inline bool valid(coord c) {return c.first < sz && c.second < sz; };

    void connect_adjacents(unsigned r, unsigned c);
    std::vector<coord> neighbours(unsigned r, unsigned c);

    std::vector<coord> row(unsigned r);
    std::vector<coord> column(unsigned c);

  public:
    percolation(unsigned n);    
    ~percolation() {delete [] id; };

    void open(unsigned r, unsigned c);
    bool is_open(unsigned r, unsigned c);
    bool is_open(coord c);
    bool check();

    std::vector<coord> points();
    int size() {return sz;};

    void print();
};

percolation generate_from_file(std::fstream& f);
