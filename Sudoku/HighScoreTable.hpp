#ifndef HIGHSCORETABLE_HPP_INCLUDED
#define HIGHSCORETABLE_HPP_INCLUDED

#include <string>
#include <vector>

class HighScoreTable
{
    const int scores_saved = 10;
    std::vector<int> times;
    std::vector<std::string> names;

public:

    HighScoreTable(std::string filename = "highscores.txt");
    bool is_on_leaderboard(int difficulty, int time);
    void add(int difficulty, int time, std::string name);
    std::string get(int difficulty);
};

#endif // HIGHSCORETABLE_HPP_INCLUDED
