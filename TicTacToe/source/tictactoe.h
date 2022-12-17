#pragma once

#include <iostream>
using namespace std;

#define BOARD { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }

void drawBoard(char board[]);

// Check if player won
bool checkWin(char board[], char playChar);

// Flip flop for bool
void bflip(bool& key);

// Prompt user for move
int promptMove(char board[], char name);

// Prompt user for exit from the program
bool askExit();

// Full raw version of Tic-Tac-Toe
void playRawTTT();


