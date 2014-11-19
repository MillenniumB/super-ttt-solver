//
//  PrintGame.h
//  SuperTicTacToeSolver
//
//  Created by Eric Zelikman on 11/19/14.
//  Copyright (c) 2014 Eric Zelikman. All rights reserved.
//

#ifndef __SuperTicTacToeSolver__PrintGame__
#define __SuperTicTacToeSolver__PrintGame__

#include <iostream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;

signed char checkboard(signed char boardin[3][3]);
void gameprint(signed char cell[3][3][3][3]);
void gameprint(signed char cell[3][3][3][3], int gamexin, int gameyin);
string numtospot(int checknum, bool maincell);
void testmove(int &boardx, int &boardy, int turn, double &won, double &paths, signed char cell[][3][3][3], int &mainturn);
void starttest(int boardx, int boardy, int turn, double &won, double &paths, signed char cell[][3][3][3], int &mainturn, int &width, int &height, double randin);
int checkgame(signed char cellin[3][3][3][3]);
void nextturn(int boardx, int boardy, int turn, signed char cell[][3][3][3]);

#endif /* defined(__SuperTicTacToeSolver__PrintGame__) */

