#pragma once

#include <iostream>
#include "../Helpers/Prompts.h"

#define BOARD { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }

void drawBoard(char board[]);

bool checkWin(char board[], char playChar);

// Flip flop for bool
void bflip(bool& key);

int promptMove(char board[], char name);

void playTTT();


