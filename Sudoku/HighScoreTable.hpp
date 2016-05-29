#ifndef HIGHSCORETABLE_HPP_INCLUDED
#define HIGHSCORETABLE_HPP_INCLUDED

#include <string>
#include <vector>
#include <array>

class HighScoreTable
{
    const int scores_saved = 10;
    const int infinity = 1 << 30;

    struct TableEntry
    {
        int time;
        std::string name;
    };

    std::array<std::vector<TableEntry>, 5> records;

public:

    HighScoreTable(std::string filename = "highscores.txt");
    bool is_on_leaderboard(int difficulty, int time);
    void add(int difficulty, int time, std::string name);
    std::string get(int difficulty);
    void save(std::string filename = "highscores.txt");
};

#endif // HIGHSCORETABLE_HPP_INCLUDED
