#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "View.hpp"
#include "Key.hpp"
#include "Color.hpp"
#include "Board.hpp"
#include "HighScoreTable.hpp"

#include <string>
#include <array>

class Game
{
    std::string server_ip;
    Board board;
    struct Position
    {
        int row, column;
    } cursor_position;
    View current_view;
    std::string playing_view, input_name_view, high_scores_view, select_difficulty_view;

    void read_user_input();
    void load_views();
    void refresh_display();
    void move_cursor(Key key);
    void quit();

public:

    Game(int argc, char **argv);
    void run();
};

#endif // GAME_HPP_INCLUDED
