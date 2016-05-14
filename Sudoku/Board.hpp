#ifndef BOARD_HPP_INCLUDED
#define BOARD_HPP_INCLUDED

#include "Color.hpp"

#include <array>
#include <vector>
#include <string>

class Board
{
    bool won, solved;
    std::array<std::array<int, 9>, 9> current_state;
    std::array<std::array<int, 9>, 9> solved_state;
    std::array<std::array<Color, 9>, 9> colors;

    bool input_legal(int row, int column);

public:

    void load_from_json(std::string json_string);
    void load_from_file(std::string filename = "save.json");
    bool game_won();
    std::vector<int> get_legal_inputs(int row, int column);
    void solve();
    const std::array<std::array<int, 9>, 9> &get_numbers();
    const std::array<std::array<Color, 9>, 9> &get_colors();
    void input(int row, int column, int number);
    void save(std::string filename = "save.json");
};

#endif // BOARD_HPP_INCLUDED
