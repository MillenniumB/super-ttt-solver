//
//  CheckN.cpp
//  SuperTicTacToeSolver
//
//  Created by Eric Zelikman on 11/19/14.
//  Copyright (c) 2014 Eric Zelikman. All rights reserved.
//

#include "TicTacToe.h"


signed char checkboard(signed char boardin[3][3])
{
    for (int test=0; test<=2; test++)
    {
        if (boardin[0][test]==boardin[1][test] && boardin[1][test]==boardin[2][test] && boardin[0][test]!=0)
        {
            return boardin[0][test];
        }
        else if (boardin[test][0]==boardin[test][1] && boardin[test][1]==boardin[test][2] && boardin[test][0]!=0)
        {
            return boardin[test][0];
        }
    }
    for (int direct=-1;direct<=1;direct+=2)
    {
        if (boardin[0][2-abs(direct-1)]==boardin[1][1] && boardin[1][1]==boardin[2][abs(direct-1)] && boardin[1][1]!=0)
        {
            return boardin[1][1];
        }
    }
    int total=0;
    for (int x=0;x<3;x++)
    {
        for (int y=0;y<3;y++)
        {
            if (boardin[x][y]!=0) total++;
        }
    }
    if (total==9) return 2;
    return 0;
}

int checkgame(signed char cellin[3][3][3][3])
{
    for (int test=0; test<=2; test++)
    {
        if (checkboard(cellin[0][test])==checkboard(cellin[1][test]) && checkboard(cellin[1][test])==checkboard(cellin[2][test]) && checkboard(cellin[0][test])!=0)
        {
            return checkboard(cellin[0][test]);
        }
        else if (checkboard(cellin[test][0])==checkboard(cellin[test][1]) && checkboard(cellin[test][1])==checkboard(cellin[test][2]) && checkboard(cellin[test][0])!=0)
        {
            return checkboard(cellin[test][0]);
        }
    }
    for (int direct=-1;direct<=1;direct+=2)
    {
        if (checkboard(cellin[0][2-abs(direct-1)])==checkboard(cellin[1][1]) && checkboard(cellin[1][1])==checkboard(cellin[2][abs(direct-1)]) && checkboard(cellin[1][1])!=0)
        {
            return checkboard(cellin[1][1]);
        }
    }
    int checkboardsolved=0;
    for (int boardx=0; boardx<3; boardx++)
    {
        for (int boardy=0; boardy<3; boardy++)
        {
            if (checkboard(cellin[boardx][boardy])==2) checkboardsolved++;
        }
    }
    if (checkboardsolved==9) return 2;
    return 0;
}

