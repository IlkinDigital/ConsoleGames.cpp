#pragma once

#include <iostream>
#include <math.h>
#include <time.h>

extern int boardSize;

void drawBoard(char** board);

int* setBoard(int mode);
int* getMixedBoard(int mode);

int getMoveableAmount(int* board);
int* getMoveableTiles(int* board);

void setBoardSize(int size);
char** setView(int* board);

bool canMove(int* board, int tile);
void moveTile(int* board, int tile);
bool isSolved(int* board);

bool askExit();
int askBSize();
int askMixMode();
int askSolveMode();

int* solvePlayer(int*& board, char**& viewBoard);
//void solveComputer(int*& board, char**& viewBoard);

void play15Puzzle();

