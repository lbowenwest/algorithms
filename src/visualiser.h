#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "percolation.h"

class visualiser {
  private:
    sf::RenderWindow& window;
    percolation& pc;

    sf::Color fg;
    sf::Color bg;
    std::vector<sf::RectangleShape> rects;
    int width;
    int height;
    
  public:
    visualiser(sf::RenderWindow& w, percolation& p);

    sf::RenderWindow& get_window();
    void update();
    void show();
};
