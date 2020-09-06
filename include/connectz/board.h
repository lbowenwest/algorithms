#pragma once

#include <unordered_map>
#include <sul/dynamic_bitset.hpp>

namespace cz {
    enum class Player : int {
        NOBODY = 0,
        PLAYER_1 = 1,
        PLAYER_2 = 2,
    };

    inline Player opponent(Player player);

    struct Dimensions {
        size_t width, height, win_length;

        [[nodiscard]] inline bool validate() const {
            return win_length <= width || win_length <= height;
        }
    };

    struct Direction {
        int delta_x, delta_y;

        Direction operator-() const {
            return Direction{-delta_x, -delta_y};
        }
    };


    struct Board {
        using index_type = size_t;
        using coord = std::pair<index_type, index_type>;

        Player current_player{Player::PLAYER_1};
        Dimensions dimensions;
        coord last_move;

        explicit Board(Dimensions dimensions);


        /**
         * Transforms a row and column into an index
         *
         * Used for accessing the grid and the mask directly
         *
         * @param column
         * @param row
         * @return
         */
        inline index_type as_index(index_type column, index_type row) const;

        /**
         * Check that the column can receive another peice
         *
         * @param column
         * @return
         */
        inline bool valid_move(index_type column) const;

        /**
         * Check that a given column and row are valid for the board
         *
         * @param column
         * @param row
         * @return
         */
        inline bool valid_position(index_type column, index_type row) const;

        /**
         * Returns the player at the given position
         *
         * @param column
         * @param row
         * @return player at position
         */
        Player at(index_type column, index_type row) const;

        /**
         * Checks if all possible moves have been made on the board
         *
         * @return true if board is full
         */
        bool full() const;

        /**
         * Adds a piece to the given column
         *
         * @param column
         */
        void make_move(index_type column, Player player);

        /**
         * Get the length of the streak along the direction
         *
         * @param start  start position
         * @param direction  direction to iterate over
         * @param player  player to get streak for
         * @return length of the streak
         */
        int get_streak(coord start, Direction direction, Player player) const;

        /**
         * Check the boards win condition
         *
         * @param start
         * @param player
         * @return
         */
        bool check_win(coord start, Player player);

        inline bool check_win(Player player) {
            return check_win(last_move, player);
        }


    private:
        int moves_made{0};
        sul::dynamic_bitset<uint32_t> grid;
        sul::dynamic_bitset<uint32_t> mask;
        std::unordered_map<index_type, index_type> row_heights;

    };

}
