#include "Board.hpp"

Board::Board()
{
    won = finished = false;
}

void Board::load_from_json(std::string json_string)
{

}

void Board::load_from_file(std::string filename)
{

}

bool Board::game_finished()
{
    return finished;
}

bool Board::game_won()
{
    return won;
}

std::vector<int> Board::get_legal_inputs(int row, int column)
{

}

void Board::solve()
{

}

const SudokuGrid<int> &Board::get_numbers()
{

}

const SudokuGrid<Color> &Board::get_colors()
{

}

void Board::input(int row, int column, int number)
{

}

void Board::save(std::string filename)
{

}

bool Board::input_legal(int row, int column)
{

}
