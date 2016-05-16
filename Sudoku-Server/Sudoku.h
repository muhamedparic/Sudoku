#ifndef SUDOKU_H
#define SUDOKU_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;



int grid[9][9] ={0, 0, 0, 3, 1, 0, 0, 0, 0,
                 3, 0, 0, 0, 0, 6, 5, 0, 0,
                 0, 0, 7, 0, 2, 5, 0, 9, 0,
                 0, 2, 0, 0, 3, 4, 8, 0, 0,
                 0, 4, 0, 0, 0, 0, 0, 5, 0,
                 0, 0, 9, 1, 8, 0, 0, 6, 0,
                 0, 7, 0, 9, 5, 0, 2, 0, 0,
                 0, 0, 8, 2, 0, 0, 0, 0, 6,
                 0, 0, 0, 0, 4, 3, 0, 0, 0
        };

class Sudoku
{
    vector<vector <int> > tabla;
    public:
        Sudoku();
        void generisiSudoku();
        void ispisiSudoku();
        bool rijesiSudoku();
        bool nadjiPraznoMjesto(int &red, int &kolona);
        bool staviBroj(int red, int kolona, int broj);
        bool brojPonovljenKolona(int kolona, int broj);
        bool brojPonovljenRed(int red, int broj);
        bool brojPonovljenKvadrat(int pocetnoI, int pocetnoJ, int broj);

};

Sudoku::Sudoku(){
    tabla.resize(9);
    for (int i = 0; i < 9; i++) tabla[i].resize(9);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            tabla[i][j] = 0;
}

void Sudoku::generisiSudoku(){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            tabla[i][j] = grid[i][j];
}

void Sudoku::ispisiSudoku(){
    ofstream fout("3.txt", ofstream::app);    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) fout << tabla[i][j];
    fout.close();
}

bool Sudoku::rijesiSudoku(){
    int red, kolona;
    if (nadjiPraznoMjesto(red,kolona)){
        for (int i = 1; i <= 9; i++)
        {
            if (staviBroj (red,kolona, i))
            {
                tabla[red][kolona] = i;
                if (rijesiSudoku())
                    return true;
                tabla[red][kolona] = 0;
            }
        }
        return false;
    }
    else
        return true;
}
bool Sudoku::nadjiPraznoMjesto(int &red, int &kolona){
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++){
            if (tabla[i][j] == 0){
                red = i; kolona = j;
                return true;
            }
    }
    return false;
}

bool Sudoku::staviBroj(int red, int kolona, int broj){
    if (!brojPonovljenRed(red,broj) && !brojPonovljenKolona(kolona, broj) && !brojPonovljenKvadrat(red - red % 3, kolona - kolona % 3, broj)) return true;
    return false;

}

bool Sudoku::brojPonovljenRed(int red, int broj){
    for (int i = 0; i < 9; i++){
        if (tabla[red][i] == broj)
            return true;
    }
    return false;
}
bool Sudoku::brojPonovljenKolona(int kolona, int broj){
    for (int i = 0; i < 9; i++){
        if (tabla[i][kolona] == broj)
            return true;
    }
    return false;
}
bool Sudoku::brojPonovljenKvadrat(int pocetnoI, int pocetnoJ, int broj){
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tabla [i + pocetnoI][j + pocetnoJ] == broj)
                return true;
    return false;
}


#endif // SUDOKU_H
