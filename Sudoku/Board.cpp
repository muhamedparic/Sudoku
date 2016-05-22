#include "Board.hpp"

#include <stdexcept>

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

void Board::load_from_string(std::string board_string)
{
    if (board_string.length() != 162)
    {
        throw std::domain_error("Neispravni podaci");
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            current_state.at(i).at(j) = board_string.at(9 * i + j) - '0';
            solved_state.at(i).at(j) = board_string.at(81 + 9 * i + j) - '0';
        }
    }

    won = finished = false;
    std::array<Color, 9> empty_color;
    empty_color.fill(Color::White);
    colors.fill(empty_color);
}

void Board::check_win_conditions()
{
    if (finished)
        return;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (current_state[i][j] == 0 || colors[i][j] == Color::Red)
                return;
        }
    }

    won = true;
    finished = true;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
            colors[i][j] = (colors[i][j] == Color::White) ? Color::White : Color::Green;
    }
}

bool Board::game_finished()
{
    return finished;
}

bool Board::game_won()
{
    return won;
}

void Board::solve()
{
    finished = true;

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        { 
            if (colors.at(i).at(j) != Color::White || !current_state.at(i).at(j))
                colors.at(i).at(j) = Color::Green;
            current_state.at(i).at(j) = solved_state.at(i).at(j);
        }
    }
}

const SudokuGrid<int> &Board::get_numbers()
{
    return current_state;
}

const SudokuGrid<Color> &Board::get_colors()
{
    return colors;
}

void Board::input(int row, int column, int number)
{
    if (finished)
        return;

    if (row >= 0 && column >= 0 && row < 9 && column < 9 && (colors.at(row).at(column) != Color::White || !current_state[row][column]))
    {   
        current_state.at(row).at(column) = number;
        colors[row][column] = Color::Yellow;
    }

    reevaluate();
}

void Board::reevaluate()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (current_state.at(i).at(j) == 0 || colors.at(i).at(j) == Color::White)
                continue;
           
            for (int k = 0; k < 9; k++)
            {
                if (k != j && current_state.at(i).at(k) == current_state.at(i).at(j))
                {
                    colors.at(i).at(j) = Color::Red;
                    break;
                }

                if (k != i && current_state.at(k).at(j) == current_state.at(i).at(j))
                {
                    colors.at(i).at(j) = Color::Red;
                    break;
                }

                int r = i - i % 3 + k / 3;
                int c = j - j % 3 + k % 3;

                if ((r != i || c != j) && current_state.at(r).at(c) == current_state.at(i).at(j))
                {
                    colors.at(i).at(j) = Color::Red;
                    break;
                }
            }

            if (colors.at(i).at(j) != Color::Red)
                colors.at(i).at(j) = Color::Yellow;
        }
    }
}
