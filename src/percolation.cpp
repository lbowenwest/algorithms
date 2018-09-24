#include "union_find.h"
#include "percolation.h"

using std::size_t;
using std::vector;
using std::pair;
using std::cout;


percolation::percolation(size_t n) : sz(n), len(n*n+2), id(new bool[n*n]()), uf(UnionFind((n*n)+2)) {
  for (auto& i : row(0))      uf.unite(len-2, index(i)); 
  for (auto& i : row(sz - 1)) uf.unite(len-1, index(i));
}


void percolation::connect_adjacents(size_t r, size_t c) {
  if (!valid(r, c)) return;
  for (auto i : neighbours(r, c))
    if (is_open(i))
      uf.unite(index(i), index(r, c));
}

vector<coord> percolation::neighbours(size_t r, size_t c) {
  vector<coord> res;
  for (auto i : vector<coord>{{r-1,c}, {r+1,c}, {r,c-1}, {r,c+1}})
    if (valid(i.first, i.second))
        res.push_back(i);
  return res;
}


void percolation::open(size_t r, size_t c) {
  if (!valid(r, c)) throw std::invalid_argument("index not in range");
  id[index(r, c)] = true;
  connect_adjacents(r, c);
}

void percolation::open(coord c) {
  open(c.first, c.second);
}

bool percolation::is_open(coord c) {
  return is_open(c.first, c.second);   
}

bool percolation::is_open(size_t r, size_t c) {
  if (!valid(r, c)) throw std::invalid_argument("index not in range");
  return id[index(r, c)];
}

vector<coord> percolation::row(size_t r) {
  if (!valid(r)) throw std::invalid_argument("index not in range"); 
  vector<coord> res;
  for (unsigned i = 0; i < sz; ++i)
    res.push_back(pair<int,int>{r, i});
  return res;
}

vector<coord> percolation::column(size_t c) {
  if (!valid(c)) throw std::invalid_argument("index not in range");
  vector<coord> res;
  for (unsigned i = 0; i < sz; ++i) {
    pair<int, int> co {i ,c};
    res.push_back(co);
  }
  return res;
}

vector<coord> percolation::points() {
  vector<coord> res;
  for (size_t i = 0; i < sz; ++i) {
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


percolation generate_from_file(std::fstream& f) {
  int size, a, b;
  vector<pair<int,int>> sites;

  if (f.is_open()) {
    f >> size;
    while (f >> a >> b)
      sites.push_back({--a, --b});
  }
  percolation pc(size);
  for (auto& c : sites)
    pc.open(c.first, c.second);

  return pc;
}
