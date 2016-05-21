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

    bool input_legal(int row, int column);
    std::string encrypt_decrypt(std::string input);

public:

    Board();
    void load_from_string(std::string board_string);
    void load_from_file(std::string filename = "save.txt");
    bool game_won();
    bool game_finished();
    std::vector<int> get_legal_inputs(int row, int column);
    void solve();
    const SudokuGrid<int> &get_numbers();
    const SudokuGrid<Color> &get_colors();
    void input(int row, int column, int number);
    void save(std::string filename = "save.txt");
};

#endif // BOARD_HPP_INCLUDED
