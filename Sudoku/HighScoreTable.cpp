#include "HighScoreTable.hpp"

#include <algorithm>
#include <fstream>

HighScoreTable::HighScoreTable(std::string filename)
{
    std::ifstream fin(filename);

    if (!fin.is_open())
    {
        std::for_each(records.begin(), records.end(), [=](std::vector<TableEntry> diff)
            {
                const TableEntry te{0, "0"};
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
            if (time)
                records.at(i / 5).push_back({time, name});
        }

        fin.close();
    }
}

bool HighScoreTable::is_on_leaderboard(int difficulty, int time)
{
   return (records.at(difficulty).size()) ? (records.at(difficulty).back().time > time) : true;
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
        table += entry.name;
        table += std::string(' ', 25 - entry.name.length());
        char time[10];
        sprintf(time, "%d", entry.time);
        table += std::string(time);
        table += std::string('\n', 1);
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
       for (int i = 0; i < (int)(scores_saved - diff.size()); i++)
           fout << "0 0\n";
   }

   fout.close();
}
