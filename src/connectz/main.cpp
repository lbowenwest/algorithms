#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "connectz/board.h"

enum class Output : int {
    DRAW = 0,
    PLAYER_1_WINS = 1,
    PLAYER_2_WINS = 2,
    INCOMPLETE = 3,
    ILLEGAL_CONTINUE = 4,
    ILLEGAL_ROW = 5,
    ILLEGAL_COLUMN = 6,
    ILLEGAL_GAME = 7,
    INVALID_FILE = 8,
    FILE_ERROR = 9
};


Output play_game(cz::Dimensions dimensions, std::vector<size_t> moves) {
    if (!dimensions.validate()) {
        return Output::ILLEGAL_GAME;
    }
    cz::Board board{dimensions};
    cz::Player player = board.current_player;

    for (auto &column : moves) {
        if (column >= board.dimensions.width) {
            return Output::ILLEGAL_COLUMN;
        }
        if (!board.valid_move(column)) {
            return Output::ILLEGAL_ROW;
        }
        board.make_move(column, player);
        if (board.check_win(player)) {
            if (&column != &moves.back()) {
                return Output::ILLEGAL_CONTINUE;
            }
            return player == cz::Player::PLAYER_1 ? Output::PLAYER_1_WINS : Output::PLAYER_2_WINS;
        }
        player = opponent(player);

    }
    return board.full() ? Output::DRAW : Output::INCOMPLETE;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "provide one input file" << std::endl;
        return 1;
    }
    const std::string file_name{argv[1]};
    std::ifstream file{file_name};
    if (!file.is_open()) {
        std::cout << static_cast<int>(Output::FILE_ERROR) << std::endl;
        return 1;
    }
    std::string line;
    std::getline(file, line);

    std::istringstream iss{line};
    size_t width, height, win_length;
    if (!(iss >> width >> height >> win_length)) {
        std::cout << static_cast<int>(Output::INVALID_FILE) << std::endl;
        return 1;
    }

    cz::Dimensions dimensions{width, height, win_length};
    if (!dimensions.validate()) {
        std::cout << static_cast<int>(Output::ILLEGAL_GAME) << std::endl;
        return 1;
    }

    size_t move;
    std::vector<size_t> moves{};
    while (file >> move) {
        moves.emplace_back(move - 1);
    }

    auto result = play_game(dimensions, moves);
    std::cout << static_cast<int>(result) << std::endl;

    return 0;

}