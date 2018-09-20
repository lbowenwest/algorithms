#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <boost/program_options.hpp>

#include "percolation.h"
#include "visualiser.h"

using std::string;
using std::vector;
namespace po = boost::program_options;


int main(int argc, char **argv) {
  string file_path;

  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce this message")
    ("file,f", po::value<string>(&file_path), "file path to read in")
    ("visualiser,v", "show visualiser");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);


  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }


  if (vm.count("file")) {
    std::ifstream file(file_path);
    int size, a, b;
    vector<std::pair<int, int>> sites;

    if (file.is_open()) {
      file >> size;
      while (file >> a >> b)
        sites.push_back({--a, --b}); // files are index based 1 annoyingly
    }

    percolation pc(size);

    for (auto& c : sites)
      pc.open(c.first, c.second);

    if (vm.count("visualiser")) {
      sf::RenderWindow window(sf::VideoMode(1000, 1000), "sfml");
      visualiser v(window, pc);
      v.show();

      return 0;
    }

    // no visualiser so just print if we percolate
    if (pc.check()) std::cout << "Percolates!" << std::endl;
    else  std::cout << "Does not percolate" << std::endl;

    return 0;

  }

  // we didn't get any options, print help and exit out
  std::cout << desc << std::endl;
  return 1;

}


