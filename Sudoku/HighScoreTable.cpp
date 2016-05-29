#include "HighScoreTable.hpp"

#include <algorithm>
#include <fstream>
#include <fstream>

HighScoreTable::HighScoreTable(std::string filename)
{
    std::ifstream fin(filename);

    if (!fin.good())
    {
        std::for_each(records.begin(), records.end(), [=](std::vector<TableEntry> &diff)
            {
                const TableEntry te{infinity, "0"};
                diff = std::vector<TableEntry>(scores_saved, te);
            });
        fin.close();
    }
    else
    {
        for (int i = 0; i < 5 * scores_saved; i++)
        {
            int time;
            std::string name;
            fin >> name >> time;
            records.at(i / 10).push_back({time, name});
        }

        fin.close();
    }
}

bool HighScoreTable::is_on_leaderboard(int difficulty, int time)
{
    return records.at(difficulty).back().time > time;
}

void HighScoreTable::add(int difficulty, int time, std::string name)
{
    records.at(difficulty).push_back({time, name});
    std::sort(records.at(difficulty).begin(), records.at(difficulty).end(), [](TableEntry te1, TableEntry te2)
        {
            return te1.time < te2.time;
        });
    records.at(difficulty).resize(scores_saved);
}

std::string HighScoreTable::get(int difficulty)
{
    std::string table;

    for (auto entry : records.at(difficulty))
    {
        if (entry.time == infinity)
            continue;

        table += entry.name;
        table += std::string(' ', 25 - entry.name.length());
        char time[10];
        sprintf(time, "%d", entry.time);
        table += std::string(time);
        table += std::string("\n");
    }

    return table;
}

void HighScoreTable::save(std::string filename)
{
   std::ofstream fout(filename);
   
   for (auto diff : records)
   {
       for (auto rec : diff)
           fout << rec.name << ' ' << rec.time << '\n';
   }

   fout.close();
}
