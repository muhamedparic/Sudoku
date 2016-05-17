#include <iostream>
#include <vector>
#include "Sudoku.h"

using namespace std;


int main(int argc, char *argv[])
{
    Sudoku s;
    s.generisiSudoku();
    s.ispisiSudoku();
    s.rijesiSudoku();
    s.ispisiSudoku();

}


