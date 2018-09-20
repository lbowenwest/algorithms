
#include "union_find.h"
#include "percolation.h"


percolation::percolation(unsigned n) : sz(n), len(n*n+2), id(new bool[n*n]()), uf(UnionFindQUW((n*n)+2)) {
  for (auto& i : row(0))      uf.unite(len-2, index(i)); 
  for (auto& i : row(sz - 1)) uf.unite(len-1, index(i));
}


void percolation::connect_adjacents(unsigned r, unsigned c) {
  if (!valid(r, c)) return;
  for (auto i : neighbours(r, c))
    if (is_open(i))
      uf.unite(index(i), index(r, c));
}

vector<coord> percolation::neighbours(unsigned r, unsigned c) {
  vector<coord> res;
  for (auto i : vector<coord>{{r-1,c}, {r+1,c}, {r,c-1}, {r,c+1}})
    if (valid(i.first, i.second))
        res.push_back(i);
  return res;
}


void percolation::open(unsigned r, unsigned c) {
  if (!valid(r, c)) throw "out of range";
  id[index(r, c)] = true;
  connect_adjacents(r, c);
}

bool percolation::is_open(coord c) {
  return is_open(c.first, c.second);   
}

bool percolation::is_open(unsigned r, unsigned c) {
  if (!valid(r, c)) throw "out of range";
  return id[index(r, c)];
}

vector<coord> percolation::row(unsigned r) {
  if (!valid(r)) throw "out of range"; 
  vector<coord> res;
  for (unsigned i = 0; i < sz; ++i)
    res.push_back(pair<int,int>{r, i});
  return res;
}

vector<coord> percolation::column(unsigned c) {
  if (!valid(c)) throw "out of range";
  vector<coord> res;
  for (unsigned i = 0; i < sz; ++i) {
    pair<int, int> co {i ,c};
    res.push_back(co);
  }
  return res;
}

vector<coord> percolation::points() {
  vector<coord> res;
  for (int i = 0; i < sz; ++i) {
    auto r = row(i);
    res.insert(res.end(), std::make_move_iterator(r.begin()), std::make_move_iterator(r.end()));
  }
  return res;
}


bool percolation::check() {
  return uf.find(len-2, len-1);
}

void percolation::print() {
  for (unsigned i = 0; i < sz; ++i) {
    for (auto& c : row(i)) {
      if (is_open(c)) cout << '*';
      else            cout << '-';
    }
    cout << '\n';
  }
}
