#pragma once

#include <vector>
#include <utility>
#include <iostream>

#include "union_find.h"

using std::vector;
using std::pair;
using std::cout;

using coord = pair<unsigned,unsigned>;

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
    vector<coord> neighbours(unsigned r, unsigned c);

    vector<coord> row(unsigned r);
    vector<coord> column(unsigned c);

  public:
    percolation(unsigned n);    
    ~percolation() {delete [] id; };

    void open(unsigned r, unsigned c);
    bool is_open(unsigned r, unsigned c);
    bool is_open(coord c);
    bool check();

    vector<coord> points();
    int size() {return sz;};

    void print();
};
