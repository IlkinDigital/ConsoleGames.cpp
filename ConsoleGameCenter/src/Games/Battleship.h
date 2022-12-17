#pragma once

#include "../Helpers/Utilities.h"
#include "../Helpers/Prompts.h"

const int row = 10;
const int col = 10;

const char initSymb = ' ';
const char missSymb = '.';
const char hitSymb = 'X';
const char carrier = 'C', bship = 'B', destroyer = 'D', submarine = 'S', pBoat = 'P';

void initGame();

char lower(char letter);

// Ships 
void manualArrange(char board[row][col]);
void autoArrange(char board[row][col]);

// Boards
void initBoard(char b[row][col], char symbol);

// User input
int askArrType();
bool askArranged();
int askGM();
int askSM();
int askDirection();
int* askEdgeCoords(char b[row][col], int direction, int shipSize);

// Displaying
void drawBoard(char b[row][col]);
void drawShips(int ships[5][3]);

// Gameplay
int* getCoords(char viewBoard[row][col]);
int getSSize(int index);

bool canShoot(int coords[], char viewBoard[row][col]);
int getPossibleMoves(int coords[], char viewBoard[row][col]);
char* getAroundDirections(int coords[], char viewBoard[row][col]);

int* shoot(int coords[], char viewBoard[row][col], char board[row][col]);
int* dummyShoot(char viewBoard[row][col], char board[row][col]);
int* smartShoot1(char viewBoard[row][col], char board[row][col]);
int* smartShoot2(char viewBoard[row][col], char board[row][col]);

// Assembly
bool doesOverlap(char vb[row][col], int r, int c, int direction, int shipSize);
bool doesCrossBorder(char vb[row][col], int r, int c, int direction, int shipSize);
void placeShip(char b[row][col], int r, int c, int direction, int shipSize, char shipSymb);

// Game
void PlayerVsComputer(int shootMode);
void ComputerVsComputer(int shootMode, const char* p1, const char* p2);

void playBattleship();