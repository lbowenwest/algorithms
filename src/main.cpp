#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

#include "percolation.h"
#include "visualiser.h"

using namespace std;

int main(int argc, char **argv) {
  string file_path;

  if (argc > 1) {
    file_path = argv[1] ;
  } else {
    file_path = "input4.txt";
  }

  int size, a, b;
  vector<pair<int, int>> sites;
  ifstream file(file_path);

  if (file.is_open()) {
    file >> size;
    while (file >> a >> b) {
      sites.push_back({--a, --b}); // files are index based 1 annoyingly
    }
  }

  percolation pc(size);
  for (auto& c : sites) {
    pc.open(c.first, c.second);
  }

  sf::RenderWindow window(sf::VideoMode(1000, 1000), "sfml");

  visualiser v(window, pc);
  v.show();

  /* while (window.isOpen()) { */
  /*     sf::Event event; */
  /*     while (window.pollEvent(event)) { */
  /*         if (event.type == sf::Event::Closed) */
  /*             window.close(); */
  /*     } */

  /*     v.update(); */
  /*     window.display(); */
  /* } */

  return 0;
}


