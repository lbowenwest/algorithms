#pragma once

class UnionFind {
  protected:
    int* elem;
    int sz;

  public: 
    UnionFind(int n) : elem(new int[n]), sz(n) {for (int i = 0; i < n; ++i) elem[i] = i; }; 
    ~UnionFind() {delete [] elem;}; 
    
    void check_inputs(int a, int b) {if (a > size() || b > size()) throw "out of error"; };
    int size() {return sz; };
};


class UnionFindQF : public UnionFind {
  public:
    UnionFindQF(int n) : UnionFind(n) {};

    bool find(int a, int b);
    void unite(int a, int b);
};


class UnionFindQU : public UnionFind {
  protected:
    virtual int root(int i);

  public:
    UnionFindQU(int n) : UnionFind(n) {};

    bool find(int a, int b);
    void unite(int a, int b);
};


class UnionFindQUW : public UnionFindQU {
  private:
    int* trees;
  
  public:
    UnionFindQUW(int n) : UnionFindQU(n), trees(new int[n]) {};
    ~UnionFindQUW() {delete [] trees;};
    void unite(int a, int b);
};


class UnionFindQUWC : public UnionFindQUW {
  protected:
    int root(int i);

  public:
    UnionFindQUWC(int n) : UnionFindQUW(n) {};
};
