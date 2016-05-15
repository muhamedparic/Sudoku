#include "Game.hpp"

#include <fstream>
#include <stdexcept>

void Game::read_user_input()
{

}

void Game::load_views()
{
    const static std::array<std::string, 4> view_names = { "playing_view", "input_name_view", "high_scores_view", "select_difficulty_view" };

    for (auto name : view_names)
    {
        std::ifstream fin(std::string("views/" + name + std::string(".txt")));

        if (!fin.is_open())
            throw std::invalid_argument("View file not found!");

        if (name == "playing_view")
            playing_view = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
        else if (name == "input_name_view")
            input_name_view = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
        else if (name == "high_scores_view")
            high_scores_view = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
        else
            select_difficulty_view = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());

        fin.close();
    }
}

void Game::refresh_display()
{

}

void Game::move_cursor(Key key)
{

}

Game::Game(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg.length() > 11 && arg.substr(0, 11) == std::string("-server-ip="))
        {
            server_ip = arg.substr(11);
            break;
        }
    }

    load_views();
}

void Game::run()
{

}
