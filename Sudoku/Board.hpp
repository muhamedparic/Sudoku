#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include "Color.hpp"

#include <array>
#include <vector>
#include <string>

template <typename T>
using SudokuGrid = std::array<std::array<T, 9>, 9>;

class Board
{
    bool won, finished;
    SudokuGrid<int> current_state;
    SudokuGrid<int> solved_state;
    SudokuGrid<Color> colors;

    void reevaluate();

public:

    Board();
    void load_from_string(std::string board_string);
    void check_win_conditions();
    bool game_won();
    bool game_finished();
    void solve();
    const SudokuGrid<int> &get_numbers();
    const SudokuGrid<Color> &get_colors();
    void input(int row, int column, int number);
};

#endif // BOARD_HPP_INCLUDED
