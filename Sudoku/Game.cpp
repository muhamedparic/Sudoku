#include "Game.hpp"

#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ncurses.h>

void Game::read_user_input()
{
	int key = getch();
	if (key == 'q')
		quit();
	else if (key == 65 && cursor_position.row > 0)
		cursor_position.row--;
	else if (key == 66 && cursor_position.row < 4)
		cursor_position.row++;
}

void Game::load_views()
{
    /*
    std::ifstream fin("/home/muhamed/Desktop/CPP/Sudoku/Sudoku/views/select_difficulty_view.txt");
    select_difficulty_view = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    printw("%s", select_difficulty_view.c_str());
    getch();
	*/
    const static std::array<std::string, 4> view_names = { "playing_view", "input_name_view", "high_scores_view", "select_difficulty_view" };

    for (auto name : view_names)
    {
        std::ifstream fin(std::string("/home/muhamed/Desktop/CPP/Sudoku/Sudoku/views/") + name + std::string(".txt"));

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
	std::array<std::string, 5> tmp_strs = {"Level 1", "Level 2", "Level 3", "Level 4", "Level 5"}; //

	clear();
	switch (current_view)
	{
		case View::SelectDifficulty:
			printw("%s", select_difficulty_view.c_str());
			init_pair(1, COLOR_BLACK, COLOR_WHITE);
			attron(COLOR_PAIR(1));
			mvprintw(1 + 2 * cursor_position.row, 2, "%s", tmp_strs[cursor_position.row].c_str());
			attroff(COLOR_PAIR(1));
			break;
	}
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
}

void Game::run()
{
	initscr();
	start_color();
	noecho();
	curs_set(0);
	load_views();
	current_view = View::SelectDifficulty;
	cursor_position.row = cursor_position.column = 0;

	while (true)
	{
		refresh_display();
		read_user_input();
	}
}

void Game::quit()
{
	endwin();
	exit(0);
}