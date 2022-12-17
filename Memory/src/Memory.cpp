#include "Memory.h"

bool isIn(char symb, char* arr, int length)
{
	for (int i = 0; i < length; i++)
		if (symb == arr[i])
			return true;

	return false;
}
bool isValidBoard(char** b, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			int counter = 0;
			char symb = b[i][j];

			for (int i2 = 0; i2 < size; i2++)
			{
				for (int j2 = 0; j2 < size; j2++)
				{
					if (b[i2][j2] == symb)
						counter++;
				}
			}

			if (counter > 2)
				return false;
		}
	}
	return true;
}

void drawBoard(char** b, int size)
{
	std::cout << "    ";

	for (int i = 0; i < size; i++)
	{
		if (i + 1 >= 10)
			std::cout << "  " << i + 1 ;
		else
			std::cout << "  " << i + 1 << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << "    +";
		for (int j = 0; j < size; j++)
		{
			std::cout << "---+";
		}
		std::cout << std::endl;

		if (i + 1 >= 10)
			std::cout << " " << i + 1 << " ";
		else
			std::cout << " " << i + 1 << "  ";

		for (int j = 0; j < size; j++)
		{
			std::cout << "| " << b[i][j] << " ";
		}
		std::cout << "|" << std::endl;
	}
	std::cout << "    +";
	for (int i = 0; i < size; i++)
	{
		std::cout << "---+";
	}
	std::cout << std::endl;
}
char** initFront(int size, char symb)
{
	char** board = new char* [size];
	for (int i = 0; i < size; i++)
		*(board + i) = new char[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			*(*(board + j) + i) = symb;

	return board;
	delete[] board;
}

char** initBoardItems(int size)
{
	if (size <= MAX_BSIZE)
	{
		char symbols[76] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@%&+1234567890-/*$!?><;";

		char* usedSymbs = new char[size * size / 2]{};
		int usCounter = 0;

		char** board = new char* [size] {};
		for (int i = 0; i < size; i++)
			*(board + i) = new char[size] {};

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size / 2; j++)
			{
				char symb;
				do
				{
					symb = symbols[rand() % (strlen(symbols) + 1)];
				} while (isIn(symb, usedSymbs, size * size / 2));

				usedSymbs[usCounter++] = symb;

				for (int n = 0; n < 2; n++)
				{
					int r, c;
					do
					{
						r = rand() % size;
						c = rand() % size;
					} while (board[r][c] != '\0');

					board[r][c] = symb;
				}
			}
		}

		return board;
		delete[] board;
	}
	
	return nullptr;
}

void turnOver(int* coords, char** frontB)
{
	frontB[coords[0]][coords[1]] = CARD_SYMB;
}
void turnOver(int* coords, char** frontB, char** itemsB)
{
	int r = coords[0], c = coords[1];

	if (frontB[r][c] == CARD_SYMB)
		frontB[r][c] = itemsB[r][c];
	else if (frontB[r][c] == itemsB[r][c])
		frontB[r][c] = CARD_SYMB;
}
void removeCard(int* coords, char** frontB)
{
	frontB[coords[0]][coords[1]] = ' ';
}

int askSize()
{
	int size;
	do
	{
		std::cout << "Enter board size: ";
		std::cin >> size;

		if (size % 2)
			std::cout << "Size should be even!" << std::endl;
		else if (size > MAX_BSIZE)
			std::cout << "Size should be at most "<< MAX_BSIZE << '!' << std::endl;
		else if (size < 2)
			std::cout << "Size should be at least 2!" << std::endl;
		else
			return size;
	} while (size % 2 || size > MAX_BSIZE || size < 2);

	return 4;
}
int* askCoords(char** itemsB, char** frontB, int size)
{
	int* coords = new int[2]{};

	int r, c;
	while (true)
	{
		std::cout << "Enter card's(to turn) row index: ";
		std::cin >> r;
		std::cout << "Enter card's(to turn) column index: ";
		std::cin >> c;

		r--; c--;

		if (r < size && r >= 0 && c < size && c >= 0)
		{
			if (frontB[r][c] == CARD_SYMB)
			{
				coords[0] = r;
				coords[1] = c;

				return coords;
			}
			else if (frontB[r][c] == ' ')
				std::cout << "There is no card there!" << std::endl;
			else
				std::cout << "This card is already turned over!" << std::endl;
		}
		else
			std::cout << "Coordinates are invalid!" << std::endl;
	}


}
