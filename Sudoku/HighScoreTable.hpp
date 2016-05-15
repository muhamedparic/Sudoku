#ifndef HIGHSCORETABLE_HPP_INCLUDED
#define HIGHSCORETABLE_HPP_INCLUDED

#include <string>

class HighScoreTable
{
    const int scores_saved = 10;
    const std::string filename;

public:

    HighScoreTable(std::string filename = "highscores.json");
    bool is_on_leaderboard(int difficulty, int time);
    void add(int difficulty, int time, std::string name);
    std::string get(int difficulty);
};

#endif // HIGHSCORETABLE_HPP_INCLUDED
