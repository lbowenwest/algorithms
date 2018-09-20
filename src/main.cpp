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


void conflicting_options(const po::variables_map& vm, const char* opt1, const char* opt2) {
  if (vm.count(opt1) && !vm[opt1].defaulted() && vm.count(opt2) && !vm[opt2].defaulted())
    throw std::logic_error(string("Conflicting options --") + opt1 + " and --" + opt2 + ".");
}

void option_dependency(const po::variables_map& vm, const char* base, const char* required) {
  if (vm.count(base) && !vm[base].defaulted())
    if (!vm.count(required) || vm[required].defaulted())
      throw std::logic_error(string("Option --") + base + " requires option --" + required + ".");
}

int main(int argc, char **argv) {
  try {
    string file_path;

    po::options_description desc("Allowed options");
    po::variables_map vm;

    desc.add_options()
      ("help,h", "produce this message")
      ("file,f", po::value<string>(&file_path), "file path to read in")
      ("visualiser,v", "show visualiser")
      ("bootstrap,b", "estimate a value for the percolation probability");

    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);


    conflicting_options(vm, "bootstrap", "file");
    option_dependency(vm, "visualiser", "file");

    // if we have the help option we don't care about anything else
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

  catch(std::exception& e) {
    std::cout << e.what() << std::endl;
    return 1;
  }

}

