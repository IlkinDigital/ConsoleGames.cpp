#pragma once

#include <math.h>

#include "../Helpers/Utilities.h"
#include "../Helpers/Prompts.h"

extern int boardSize;

void drawBoard(char** board);

int* getMixedBoard();

int getMoveableAmount(int* board);
int* getMoveableTiles(int* board);

void setBoardSize(int size);
char** setView(int* board);

bool canMove(int* board, int tile);
void moveTile(int* board, int tile);
bool isSolved(int* board);

int askBSize();
int askMixMode();
int askSolveMode();

int* solvePlayer(int*& board, char**& viewBoard);

void play15Puzzle();

