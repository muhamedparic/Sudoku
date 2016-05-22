#include "Game.hpp"

#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <map>
#include <vector>
#include <iostream>
#include <cstdio>

#include <ncurses.h>

void Game::read_user_input()
{
    wchar_t key_raw = getch();
    
    Key key;

    if (current_view == View::Playing && key_raw > '0' && key_raw <= '9')
    {
        board.input(cursor_position.row, cursor_position.column, key_raw - '0');
    }
    else
    {
        switch (key_raw)
        {
            case KEY_UP:
                key = Key::Up;
                break;
            case KEY_DOWN:
                key = Key::Down;
                break;
            case KEY_LEFT:
                key = Key::Left;
                break;
            case KEY_RIGHT:
                key = Key::Right;
                break;
            case 10: // NOTE: Mozda nece raditi
                key = Key::Enter;
                break;
            case 'q':
                key = Key::Esc;
                break;
            case KEY_DC:
                key = Key::Delete;
                break;
        }
    }
    move_cursor(key);
    
    // Klikovi na dugmad
    if (key == Key::Enter)
    {
        switch (current_view)
        {
            case View::Playing:
                if (cursor_position.column == 9)
                {
                    switch (cursor_position.row)
                    {
                        case 0:
                            current_view = View::SelectDifficulty;
                            cursor_position.row = cursor_position.column = 0;
                            break;
                        case 1:
                            board.solve();
                            break;
                        case 2:
                            current_view = View::HighScores;
                            cursor_position.row = 0;
                            cursor_position.column = difficulty;
                            break;
                        case 3:
                            quit();
                            break;
                        default:
                            break;
                    }
                }
                break;
            case View::SelectDifficulty:
                difficulty = cursor_position.row;
                fetch_board(difficulty);
                current_view = View::Playing;
                cursor_position.row = cursor_position.column = 0;
                break;
            default:
                break;    
        }
    }

    if (key == Key::Esc)
    {
        switch (current_view)
        {
            case View::HighScores:
                current_view = View::Playing;
                cursor_position.row = cursor_position.column = 0;
                break;
            case View::Playing:
                cursor_position.row = 3;
                cursor_position.column = 9;
                break;
            default:
                break;
        }
    }
}

void Game::fetch_board(int difficulty)
{
    // NOTE: python ili python3
    //system((std::string("python3 ") + server_ip + std::string(" ") + std::string(difficulty + '0', 1)).c_str()); DEBUG
    try
    {
        std::ifstream fin("board.txt");
        std::string input;
        fin >> input;
        board.load_from_string(input);
        // std::remove("board.txt"); DEBUG
    }
    catch (...)
    {
        throw std::domain_error("Board fetch problem!");
    }
}

void Game::load_views()
{
    const static std::array<std::string, 4> view_names = { "playing_view", "input_name_view", "high_scores_view", "select_difficulty_view" };

    for (auto name : view_names)
    {
        std::ifstream fin(std::string("views/") + name + std::string(".txt"));

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
	const char *raw_text_difficulty[] = {
    "    Trivial    ",
    "   Very easy   ",
    "  Challenging  ",
    " Somewhat evil ",
    " Insanely evil "};
    
    const char *raw_text_playing[] = {
    "     New     ",
    "    Solve    ",
    " High scores ",
    "   Abandon   "};
    
    std::map<View, std::vector<std::string>> button_text;
    
    button_text[View::SelectDifficulty] = 
        std::vector<std::string>(raw_text_difficulty, std::end(raw_text_difficulty));
    
    button_text[View::Playing] = 
        std::vector<std::string>(raw_text_playing, std::end(raw_text_playing));
    
    button_text[View::HighScores] =
        std::vector<std::string>(raw_text_difficulty, std::end(raw_text_difficulty));

    // Crtanje se vrsi u 3 koraka:
    // 1. Crtanje view-a (backgrounda)
    // 2. Crtanje dodatnih elemenata (score-ova, brojeva na ploci)
    // 3. Crtanje selektovanog elementa (invertovane boje teksta i backgrounda)
    
   clear();
   std::string name; 
   switch (current_view)
   {
       case View::SelectDifficulty:
           // 1. korak
           mvprintw(0, 0, "%s", select_difficulty_view.c_str());
           // 3. korak
           attron(COLOR_PAIR(1)); // Crni tekst sa bijelim backgroundom
           mvprintw(2 + 2 * cursor_position.row, 2, "%s", button_text[current_view].at(cursor_position.row).c_str());
           attroff(COLOR_PAIR(1));
           break;
       case View::InputName:
           // 1. korak
           mvprintw(0, 0, "%s", input_name_view.c_str());
           std::cin >> name;
           high_score_table.add(difficulty, difftime(start_time, time(NULL)), name);
           current_view = View::HighScores;
           cursor_position.row = 0;
           cursor_position.column = difficulty;           
           break;
       case View::Playing:
           // 1. korak
           mvprintw(0, 0, "%s", playing_view.c_str());
           // 2. korak
           for (int brow = 0; brow < 3; brow++)
           {
               for (int bcol = 0; bcol < 3; bcol++)
               {
                   for (int row = 0; row < 3; row++)
                   {
                       for (int col = 0; col < 3; col++)
                       {
                           Color color = board.get_colors().at(3 * brow + row).at(3 * bcol + col);
                           int number = board.get_numbers().at(3 * brow + row).at(3 * bcol + col);
                           if (!number)
                               continue;
                           int ypos = 2 + 5 * brow + row;
                           int xpos = 1 + 14 * bcol + 4 * col;
                           
                           switch (color)
                           {
                               case Color::White:
                                   mvprintw(ypos, xpos, "%d", number);
                                   break;
                               case Color::Yellow:
                                   attron(COLOR_PAIR(6));
                                   mvprintw(ypos, xpos, "%d", number);
                                   attroff(COLOR_PAIR(6));
                                   break;
                               case Color::Red:
                                   attron(COLOR_PAIR(2));
                                   mvprintw(ypos, xpos, "%d", number);
                                   attroff(COLOR_PAIR(2));
                                   break;
                               case Color::Green:
                                   attron(COLOR_PAIR(4));
                                   mvprintw(ypos, xpos, "%d", number);
                                   attroff(COLOR_PAIR(4));
                           }                
                       }
                   }
               }
           }
           // 3. korak
           if (cursor_position.column < 9) // Na nekom od brojeva, ne na button-u sa strane
           {
               Color color = board.get_colors().at(cursor_position.row).at(cursor_position.column);
               int number = board.get_numbers().at(cursor_position.row).at(cursor_position.column);
               int ypos = 2 + 5 * (cursor_position.row / 3) + (cursor_position.row % 3);
               int xpos = 1 + 14 * (cursor_position.column / 3) + 4 *  (cursor_position.column % 3);
               
               if (color == Color::White || !number)
               {
                   attron(COLOR_PAIR(1));
                   if (number)
                       mvprintw(ypos, xpos, "%d", number);
                   else
                       mvprintw(ypos, xpos, " ");
                   attroff(COLOR_PAIR(1));
               }
               else
               {
                   switch (color)
                   {
                       case Color::Yellow:
                           attron(COLOR_PAIR(7));
                           mvprintw(ypos, xpos, "%d", number);
                           attroff(COLOR_PAIR(7));
                           break;
                       case Color::Red:
                           attron(COLOR_PAIR(3));
                           mvprintw(ypos, xpos, "%d", number);
                           attroff(COLOR_PAIR(3));
                           break;
                       case Color::Green:
                           attron(COLOR_PAIR(5));
                           mvprintw(ypos, xpos, "%d", number);
                           attroff(COLOR_PAIR(5));
                           break;
                       default:
                           break;
                   }
               }
           }
           else // Na button-u
           {
               attron(COLOR_PAIR(1));
               mvprintw((cursor_position.row < 3) ? 2 + cursor_position.row : 14, 41, "%s", 
                   button_text[View::Playing].at(cursor_position.row).c_str());
               attroff(COLOR_PAIR(1));
           }
           break;
       case View::HighScores:
           // 1. korak
           mvprintw(0, 0, "%s", high_scores_view.c_str());
           // 2. korak
           mvprintw(4, 0, "%s", high_score_table.get(cursor_position.row + 1).c_str());
           // 3. korak
           attron(COLOR_PAIR(1));
           mvprintw(1, 1 + 18 * cursor_position.column, "%s", button_text[View::HighScores][cursor_position.column].c_str());
           attroff(COLOR_PAIR(1));
           break;    
   }
   refresh();
}

void Game::move_cursor(Key key)
{
    switch (key)
    {
        case Key::Up:
            switch (current_view)
            {
                case View::Playing:
                    if (cursor_position.row > 0) // NOTE: Zadnji button ima row 3, ne 8
                        cursor_position.row--;
                    break;
                case View::InputName:
                    break;
                case View::HighScores:
                    break;
                case View::SelectDifficulty:
                    if (cursor_position.row > 0)
                        cursor_position.row--;
                    break;
            }
            break;
        case Key::Down:
            switch (current_view)
            {
                case View::Playing:
                    if (cursor_position.column < 9 && cursor_position.row < 8)
                        cursor_position.row++;
                    else if (cursor_position.column == 9 && cursor_position.row < 3)
                        cursor_position.row++;
                    break;
                case View::InputName:
                    break;
                case View::HighScores:
                    break;
                case View::SelectDifficulty:
                    if (cursor_position.row < 4)
                        cursor_position.row++;
                    break;
            }
            break;
        case Key::Left:
            switch (current_view)
            {
                case View::Playing:
                    if (cursor_position.column > 0 && (cursor_position.column != 9 || cursor_position.row != 3))
                        cursor_position.column--;
                    else if (cursor_position.column == 9 && cursor_position.row == 3)
                    {
                        cursor_position.row = 8;
                        cursor_position.column = 8;
                    }
                    break;
                case View::InputName:
                    break;
                case View::HighScores:
                    if (cursor_position.column > 0)
                        cursor_position.column--;
                    break;
                case View::SelectDifficulty:
                    break;
            }
            break;
        case Key::Right:
            switch (current_view)
            {
                case View::Playing:
                    if (cursor_position.column < 8)
                        cursor_position.column++;
                    else if (cursor_position.column == 8 && cursor_position.row < 3)
                        cursor_position.column++;
                    else if (cursor_position.column == 8 && cursor_position.row == 8)
                    {
                        cursor_position.row = 3;
                        cursor_position.column = 9;
                    }
                    break;
                case View::InputName:
                    break;
                case View::HighScores:
                    if (cursor_position.column < 4)
                        cursor_position.column++;
                    break;
                case View::SelectDifficulty:
                    break;
            }
            break;
        default:
            break;
    }
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

void Game::check_win_conditions()
{
    board.check_win_conditions();
    if (board.game_won())
    {
        auto time_now = time(NULL);
        unsigned int play_time = difftime(time_now, start_time);

        if (high_score_table.is_on_leaderboard(difficulty, play_time))
        {
            current_view = View::InputName;
        }
    }
}

void Game::run()
{
	// ncurses inicijalizacija
    initscr();
	start_color();
	noecho();
	curs_set(0);
    keypad(stdscr, TRUE);
    init_color(4, 0, 1000, 0); // Suprotno od crvene 
	init_color(5, 1000, 0, 0); // Suprotno od zelene
    init_color(6, 1000, 0, 1000); // Suprotno od zute
    init_pair(1, COLOR_BLACK, COLOR_WHITE); // Invertovana bijela
    init_pair(2, 1, COLOR_BLACK); // Crvena
    init_pair(3, 4, COLOR_WHITE); // Invertovana crvena
    init_pair(4, 2, COLOR_BLACK); // Zelena
    init_pair(5, 5, COLOR_WHITE); // Invertovana zelena
    init_pair(6, 3, COLOR_BLACK); // Zuta
    init_pair(7, 6, COLOR_WHITE); // Inverovana zuta

    load_views();
	current_view = View::SelectDifficulty;
    //current_view = View::Playing;
    cursor_position.row = cursor_position.column = 0;
    start_time = time(NULL);
    
    try
    {
	    while (true)
	    {
		    refresh_display();
		    read_user_input();
            check_win_conditions();
	    }
    }
    catch (...)
    {
        endwin();
        printf("Nekakav problem");
        exit(0);
    }
}

void Game::quit()
{
	endwin();
	exit(0);
}
