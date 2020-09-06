#include <iostream>
#include <string>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <argh.h>
#include <fmt/core.h>

#include <algorithms/percolation.h>
#include <percolate/visualiser.h>


int main(int, char **argv) {

    argh::parser cmdl({"-f", "--file"});
    cmdl.parse(argv);

    const std::string description = R"(percolate
    -h --help           show help text
    -f --file [FILE]    process file
    -v --visualiser     show the visualiser
)";

    if (cmdl[{"h", "help"}]) {
        std::cout << description << std::endl;
        return EXIT_SUCCESS;
    }

    try {
        std::string file_name{cmdl({"f", "file"}).str()};
        std::fstream file{file_name};
        if (!file.is_open()) {
            throw std::invalid_argument(fmt::format("could not read file: {}", file_name));
        }
        algo::percolation pc{algo::percolation::generate_from_file(file)};

        if (cmdl[{"v", "visualiser"}]) {
            sf::RenderWindow window(sf::VideoMode(1000, 1000), "sfml");
            algo::visualiser v(window, pc);
            v.show();
        }
        else {
            // no visualiser so just print if we percolate
            std::cout << (pc.check() ? "Percolates!" : "Does not percolate") << std::endl;
        }

        return EXIT_SUCCESS;
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }

}

