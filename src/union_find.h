#pragma once

#include <stdexcept>
#include <utility>

class UnionFind {
  public:
    UnionFind(std::size_t n);
    ~UnionFind();

    std::size_t size();
    bool find(std::size_t a, std::size_t b);
    void unite(std::size_t a, std::size_t b);

  private:
    std::size_t* elem;
    std::size_t sz;
    std::size_t* trees;

    bool valid(std::size_t a);
    std::size_t root(std::size_t i);
};

