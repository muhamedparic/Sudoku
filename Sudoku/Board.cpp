#include "Board.hpp"

Board::Board()
{
    won = finished = false;
    
    // Inicijalizacija boja i brojeva na neku vrijednost
    // Vjerovatno nece trebati u krajnjoj verziji
    std::array<int, 9> empty_number;
    empty_number.fill(0);
    current_state.fill(empty_number);
    solved_state.fill(empty_number);
    
    std::array<Color, 9> empty_color;
    empty_color.fill(Color::White);
    colors.fill(empty_color);
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
    return current_state;
}

const SudokuGrid<Color> &Board::get_colors()
{
    return colors;
}

void Board::input(int row, int column, int number) // NOTE: Provjeriti validnost reda i kolone
{

}

void Board::save(std::string filename)
{

}

bool Board::input_legal(int row, int column)
{

}
