#include "union_find.h"

bool UnionFindQF::find(int a, int b) {
  check_inputs(a, b);
  return elem[a] == elem[b];
}

void UnionFindQF::unite(int a, int b) {
  check_inputs(a, b);
  int aval = elem[a];
  int bval = elem[b];
  for (int i = 0; i < sz; ++i) {
    if (elem[i] == aval) elem[i] = bval;
  }
}



int UnionFindQU::root(int i) {
  while (i != elem[i]) i = elem[i];
  return i;
}

bool UnionFindQU::find(int a, int b) {
  check_inputs(a, b);
  return root(a) == root(b);
}

void UnionFindQU::unite(int a, int b) {
  check_inputs(a, b);
  elem[root(a)] = root(b);
}



void UnionFindQUW::unite(int a, int b) {
  check_inputs(a, b);
  int i = root(a), j = root(b);
  if (i == j) return;

  if (trees[i] < trees[j]) {
    elem[i] = j;
    trees[j] += trees[i];
  } else {
    elem[j] = i;
    trees[i] += trees[j];
  }
}



int UnionFindQUWC::root(int i) {
  while (i != elem[i]) {
    elem[i] = elem[elem[i]];
    i = elem[i];
  }
  return i;
}
