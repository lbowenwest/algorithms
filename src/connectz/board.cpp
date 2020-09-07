#include "connectz/board.h"

#include <unordered_map>
#include <sul/dynamic_bitset.hpp>

namespace cz {
    Player opponent(Player player) {
        switch (player) {
            case Player::PLAYER_1:
                return Player::PLAYER_2;
            case Player::PLAYER_2:
                return Player::PLAYER_1;
            default:
                return Player::NOBODY;
        }
    }

    Board::Board(Dimensions dimensions)
            : dimensions{dimensions},
              grid(dimensions.width * dimensions.height, 0),
              mask(dimensions.width * dimensions.height, 0) {

        assert(dimensions.validate());
    }

    Board::index_type Board::as_index(const index_type column, const index_type row) const {
        return column * dimensions.height + row;
    }

    bool Board::valid_move(const index_type column) const {
        if (column >= dimensions.width)
            return false;
        return !mask.test(as_index(column, dimensions.height - 1));
    }

    bool Board::valid_position(const index_type column, const index_type row) const {
        return column < dimensions.width && row < dimensions.height;
    }

    bool Board::full() const {
        return mask.all();
    }

    Player Board::at(const index_type column, const index_type row) const {
        auto index = as_index(column, row);
        if (!mask.test(index))
            return Player::NOBODY;

        return grid.test(index) ? current_player : opponent(current_player);
    }

    void Board::make_move(const index_type column, const Player player) {
        assert(valid_move(column));
        auto &row = row_heights[column];
        auto index = as_index(column, row);
        last_move = {column, row};
        row++;
        moves_made++;

        mask.set(index);
        grid.set(index, player == current_player);
    }

    bool Board::check_win(const coord start, Player player) {
        if (moves_made < dimensions.win_length * 2 - 1)
            return false;
        std::array<Direction, 4> directions{Direction{0, 1}, Direction{1, 1}, Direction{1, 0}, Direction{-1, 1}};
        return std::any_of(directions.begin(), directions.end(), [&start, &player, this](Direction dir) {
            return get_streak(start, dir, player) >= dimensions.win_length;
        });
    }

    int Board::get_streak(const coord start, const Direction direction, const Player player) const {
        int length{0};
        auto [column, row] = start;
        while (valid_position(column, row) && at(column, row) == player) {
            length++;
            column += direction.delta_x;
            row += direction.delta_y;
        }
        column = start.first - direction.delta_x, row = start.second - direction.delta_y;
        while (valid_position(column, row) && at(column, row) == player) {
            length++;
            column -= direction.delta_x;
            row -= direction.delta_y;
        }
        return length;
    }

}
