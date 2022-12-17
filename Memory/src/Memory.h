#pragma once

#include <iostream>
#include <time.h>
#include <windows.h>
#define MAX_BSIZE 12
#define CARD_SYMB '#'

// Utils
bool isIn(char symb, char* arr, int length);
bool isValidBoard(char** b, int size);

// UI
void drawBoard(char** b, int size);
char** initFront(int size, char symb = CARD_SYMB);
char** initBoardItems(int size);

// Gameplay
void turnOver(int* coords, char** frontB, char** itemsB);
void turnOver(int* coords, char** frontB);
void removeCard(int* coords, char** frontB);

// Input
int askSize();
int* askCoords(char** itemsB, char** frontB, int size);

