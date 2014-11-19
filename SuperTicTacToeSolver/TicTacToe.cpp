#include "TicTacToe.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;


mt19937 generator((unsigned int)chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_real_distribution<double> randge(0,1);
double probabil;

void copycell(signed char cell[3][3][3][3], signed char cell2[3][3][3][3])
{
    for (int a=0;a<3;a++) for (int b=0;b<3;b++) for (int c=0;c<3;c++) for (int d=0;d<3;d++) cell[a][b][c][d]=cell2[a][b][c][d];
}

string numtospot(int checknum, bool maincell)
{
    string retchar=" ";
    if (checknum== 1) retchar=" X";
    if (checknum== 0) maincell?retchar=" ░":retchar=" ";
    if (checknum==-1) retchar=" O";
    return retchar;
}


bool wonup(double &won, double &paths, int &mainturn, signed char cell[3][3][3][3])
{
    if (checkgame(cell)!=0)
    {
        if (mainturn==checkgame(cell))
        {
            won++;
            /*if ((int)won%1000000==0)
            {
                cout << won << endl;
            }*/
        }
        paths++;
        return true;
    }
    return false;
}

void testmove(int &boardx, int &boardy, int turn, double &won, double &paths, signed char cell[3][3][3][3], int &mainturn)
{
    for (int i=0;i<=2;i++)
    {
        for (int j=0;j<=2;j++)
        {
            if (checkboard(cell[boardx][boardy])!=0)
            {
                for (int checknextx=0; checknextx<=2; checknextx++)
                {
                    for (int checknexty=0; checknexty<=2; checknexty++)
                    {
                        if ((checkboard(cell[checknextx][checknexty])==0) && (cell[checknextx][checknexty][i][j]==0))
                        {
                            starttest(checknextx, checknexty, turn, won, paths, cell, mainturn, i, j, randge(generator));
                        }
                    }
                }
            }
            else if (cell[boardx][boardy][i][j]==0)
            {
                starttest(boardx, boardy, turn, won, paths, cell, mainturn, i, j, randge(generator));
            }
        }
    }
}

void starttest(int boardx, int boardy, int turn, double &won, double &paths, signed char cell2[][3][3][3], int &mainturn, int &width, int &height, double randin)
{
    signed char cell[3][3][3][3]={0};
    copycell(cell,cell2);
    cell[boardx][boardy][width][height]=turn;
    if (wonup(won, paths, mainturn, cell)) return;
    if (randin>probabil)
    {
        testmove(width, height, -turn, won, paths, cell, mainturn);
    }
}

void nextmove(signed char cell[][3][3][3], int turn, int gamey, int gamex)
{
    (checkboard(cell[gamex-1][gamey-1])!=0)?gameprint(cell):gameprint(cell,gamex,gamey);
    int boardx=0;
    bool movemade=false;
    int boardy=0;
    while (!movemade)
    {
        if (checkboard(cell[gamey-1][gamex-1])!=0)
        {
            cout << "Which board x? ";
            cin >> gamex;
            cout << "Which board y? ";
            cin >> gamey;
        }
        cout << "Which cell x? ";
        cin >> boardx;
        cout << "Which cell y? ";
        cin >> boardy;
        if (cell[gamey-1][gamex-1][boardy-1][boardx-1]==0)
        {
            cell[gamey-1][gamex-1][boardy-1][boardx-1]=-1;
            movemade=true;
        }
    }
    probabil*=1-pow((1-sqrt(probabil)),2);
    cout << setprecision(5) << probabil <<endl;
    nextturn(boardy-1, boardx-1, turn, cell);
}


double testopponent(int boardx, int boardy, int turn, signed char cell2[][3][3][3],int xx, int xy, int yx, int yy)
{
    signed char cell[3][3][3][3]={0};
    copycell(cell,cell2);
    cell[xx][xy][yx][yy]=turn;
    int boardmax[2];
    boardmax[0]=boardx;
    boardmax[1]=boardy;
    double bestmove=0;
    for (int i=0;i<=2;i++)
    {
        for (int j=0;j<=2;j++)
        {
            if (checkboard(cell[boardx][boardy])!=0)
            {
                for (int checknextx=0; checknextx<=2; checknextx++)
                {
                    for (int checknexty=0; checknexty<=2; checknexty++)
                    {
                        if (checkboard(cell[checknextx][checknexty])==0)
                        {
                            double won=0;
                            double paths=0;
                            if (cell[boardx][boardy][i][j]==0)
                            {
                                for (int startp=0; startp<10000 && won==0; startp++)
                                {
                                    starttest(checknextx, checknexty, turn, won, paths, cell, turn, i, j,1);
                                }
                            }
                            if (bestmove<(won/paths))
                            {
                                cout << (won/paths) << " ";
                                bestmove=(won/paths);
                                boardmax[0]=checknextx;
                                boardmax[1]=checknexty;
                            }
                        }
                    }
                }
            }
            else if (cell[boardx][boardy][i][j]==0)
            {
                double won=0;
                double paths=0;
                for (int startp=0; startp<1000 && won==0; startp++)
                {
                    starttest(boardx, boardy, turn, won, paths, cell, turn, i, j,1);
                }
                if (bestmove<(won/paths)) bestmove=(won/paths);
            }
        }
    }
    return bestmove;
}

void nextturn(int boardx, int boardy, int turn, signed char cell[][3][3][3])
{
    double opwon=1;
    gameprint(cell);
    if (checkgame(cell)!=0)
    {
        return;
    }
    int boardmax[2];
    boardmax[0]=boardx;
    boardmax[1]=boardy;
    double bestmove[3]={0,0,0};
    for (int i=0;i<=2;i++)
    {
        for (int j=0;j<=2;j++)
        {
            if (checkboard(cell[boardx][boardy])!=0)
            {
                for (int checknextx=0; checknextx<=2; checknextx++)
                {
                    for (int checknexty=0; checknexty<=2; checknexty++)
                    {
                        if (checkboard(cell[checknextx][checknexty])==0)
                        {
                            double won=0;
                            double paths=0;
                            if (cell[boardx][boardy][i][j]==0)
                            {
                                for (int startp=0; startp<10000 && won==0; startp++)
                                {
                                    starttest(checknextx, checknexty, turn, won, paths, cell, turn, i, j,1);
                                    opwon=testopponent(checknextx,checknexty, -turn, cell, checknextx, checknexty, i, j);
                                }
                            }
                            if (bestmove[2]<(won/paths/opwon))
                            {
                                bestmove[0]=i;
                                bestmove[1]=j;
                                bestmove[2]=(won/paths/opwon);
                                boardmax[0]=checknextx;
                                boardmax[1]=checknexty;
                            }
                        }
                    }
                }
            }
            else if (cell[boardx][boardy][i][j]==0)
            {
                double won=0;
                double paths=0;
                for (int startp=0; startp<1000 && won==0; startp++)
                {
                    starttest(boardx, boardy, turn, won, paths, cell, turn, i, j,1);
                }
                opwon=testopponent(boardx,boardy, -turn, cell, boardx, boardy, i, j);
                cout << setw(5) << setprecision(2) << floor(100*won/paths)/100 << ((j==2)?"\n":" ");
                if (bestmove[2]<(won/paths/opwon))
                {
                    bestmove[0]=i;
                    bestmove[1]=j;
                    bestmove[2]=(won/paths/opwon);
                }
            }
            else
            {
                cout << setw(5) << setprecision(2) << " " << ((j==2)?"\n":" ");
            }
        }
    }
    
    if (bestmove[2]!=0)
    {
        cell[boardmax[0]][boardmax[1]][(int)bestmove[0]][(int)bestmove[1]]=turn;
        nextmove(cell, turn,(int)bestmove[0]+1,(int)bestmove[1]+1);
    }
    else if (bestmove[2]==0)
    {
        nextturn(boardx, boardy,  turn, cell);
    }
}

void startgame()
{
    int startturn=1;
    for (int startposx=0; startposx<=1;startposx++)
    {
        for (int startposy=(0+startposx); startposy<=1;startposy++)
        {
            int wonthus=0;
            int lossthus=0;
            int tiedthus=0;
            for (int timesn=0;timesn<10;timesn++)
            {
                signed char cell[3][3][3][3]={0};
                nextturn(startposx,startposy,startturn,cell);
                gameprint(cell);
                int checkedn=checkgame(cell);
                if (checkedn==-1) lossthus++;
                if (checkedn== 1)  wonthus++;
                if (checkedn== 2) tiedthus++;
                cout << endl << endl;
            }
            cout << wonthus << " " << lossthus << " " << tiedthus;
        }
    }
    return;
}


int main(int argc, const char * argv[])
{
    double defprob=.89;
    cout << "Probability 0 to 1 [" <<defprob<<" default] ";
    cin >> probabil;
    if (probabil<0 || probabil>1) probabil=defprob;
    double starttime=chrono::high_resolution_clock::now().time_since_epoch().count();
    startgame();
    double totaltime=chrono::high_resolution_clock::now().time_since_epoch().count()-starttime;
    cout << "Time=" << totaltime << endl;
}