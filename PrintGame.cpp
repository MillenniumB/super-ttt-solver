#include "TicTacToe.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

void gameprint(signed char cell[3][3][3][3])
{
    for (int gamex=0;gamex<3;gamex++)
    {
        for (int gamey=0;gamey<3;gamey++)
        {
            for (int boardy=0; boardy<3;boardy++)
            {
                for (int boardx=0;boardx<3;boardx++)
                {
                    cout << setw(2) << numtospot((int)cell[gamex][boardy][gamey][boardx],false) << ((gamey%3!=2)?" ":"_");
                }
                cout << "|";
            }
            cout << endl;
        }
    }
    cout << endl;
}

void gameprint(signed char cell[3][3][3][3], int gamexin, int gameyin)
{
    for (int gamex=0;gamex<3;gamex++)
    {
        for (int gamey=0;gamey<3;gamey++)
        {
            for (int boardy=0; boardy<3;boardy++)
            {
                for (int boardx=0;boardx<3;boardx++)
                {
                    cout << setw(2);
                    if (gamexin<-1) cout << setw(2) << numtospot((int)cell[gamex][boardy][gamey][boardx],false) << ((gamey%3!=2)?" ":"_");
                    else cout << numtospot((int)cell[gamex][boardy][gamey][boardx],(gamexin-1==boardy && gameyin-1==gamex)) << ((gamey%3!=2)?" ":"_");
                }
                cout << "|";
            }
            cout << endl;
        }
    }
    cout << endl;
}
