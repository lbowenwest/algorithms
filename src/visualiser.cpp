#include "visualiser.h"

visualiser::visualiser(sf::RenderWindow& w, percolation& p) : window(w), pc(p) {
  width = w.getSize().x / p.size();
  height = w.getSize().y / p.size();

  for (auto& c : p.points()) {
    auto r = sf::RectangleShape(sf::Vector2f(width, height));
    r.setPosition(c.second * width, c.first * height);
    r.setOutlineThickness(5);
    r.setOutlineColor(bg);
    r.setFillColor(bg);
    rects.push_back(r);
  }

  if (p.check()) fg = sf::Color(102, 197, 242);
  else fg = sf::Color(255, 255, 255);
  bg = sf::Color(20, 20, 20);

}

sf::RenderWindow& visualiser::get_window() {
  return window;
}

void visualiser::update() {
  window.clear();
  auto p = pc.points();
  for (std::size_t i = 0; i < p.size(); ++i) {
    if (pc.is_open(p[i])) rects[i].setFillColor(fg);
    else                  rects[i].setFillColor(bg);
    window.draw(rects[i]);
  }
}

void visualiser::show() {
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    update();
    window.display();
  }
}





