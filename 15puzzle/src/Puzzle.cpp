#include "Puzzle.h"

int boardSize = 16;

int randint(int left, int right)
{
	if (right == left)
		return right;

	return rand() % (right - left + 1) + left;
}

void drawBoard(char** viewBoard)
{
	int counter = 0;

	std::cout << std::endl;
	for (int n = 0; n < sqrt(boardSize); n++)
	{
		std::cout << "  ";
		for (int i = 0; i < sqrt(boardSize); i++)
			std::cout << "+----";
		std::cout << "+" << std::endl;

		std::cout << "  |";
		for (int i = 0; i < sqrt(boardSize); i++)
			std::cout << " " << viewBoard[counter++] << " |";
		std::cout << std::endl;
	}

	std::cout << "  ";
	for (int i = 0; i < sqrt(boardSize); i++)
		std::cout << "+----";
	std::cout << "+" << std::endl;
}
int* setBoard(int mode)
{
	int* possibleTiles = new int[boardSize];
	int* board = new int[boardSize];

	// set possible tiles
	for (int i = 0; i < boardSize; i++)
		possibleTiles[i] = i;


	srand(time(NULL));
	for (int i = 0; i < boardSize; i++)
	{
		while (true)
		{
			int randNum = rand() % boardSize;
			if (possibleTiles[randNum] != -1)
			{
				board[i] = possibleTiles[randNum];
				possibleTiles[randNum] = -1;
				break;
			}
		}
	}

	return board;
	delete[] board;
}
int* getMixedBoard(int mode)
{
	int* board = new int[boardSize];

	for (int i = 0; i < boardSize - 1; i++)
		board[i] = i + 1;
	board[boardSize - 1] = 0;

	for (int i = 0; i < randint(250, 500); i++)
	{
		int moveableAmount = getMoveableAmount(board);
		int* moveableTiles = getMoveableTiles(board);

		moveTile(board, moveableTiles[randint(0, moveableAmount - 1)]);
	}

	return board;
	delete[] board;
}
int getMoveableAmount(int* board)
{
	int counter = 0;

	for (int i = 0; i < boardSize; i++)
	{
		if (board[i] == 0)
		{
			if (i + 1 < boardSize)
				counter++;
			if (i - 1 >= 0)
				counter++;
			if (i + (int)sqrt(boardSize) < boardSize)
				counter++;
			if (i - (int)sqrt(boardSize) >= 0)
				counter++;
			break;
		}
	}

	return counter;
}
int* getMoveableTiles(int* board)
{
	int* tiles = new int[getMoveableAmount(board)]{};

	int counter = 0;

	for (int i = 0; i < boardSize; i++)
	{
		if (board[i] == 0)
		{
			if (i - (int)sqrt(boardSize) >= 0)
				tiles[counter++] = board[i - (int)sqrt(boardSize)];
			if (i - 1 >= 0)
				tiles[counter++] = board[i - 1];
			if (i + 1 < boardSize)
				tiles[counter++] = board[i + 1];
			if (i + (int)sqrt(boardSize) < boardSize)
				tiles[counter] = board[i + (int)sqrt(boardSize)];
			break;
		}
	}

	return tiles;
	delete[] tiles;
}
char** setView(int* board)
{
	char** vBoard = new char* [boardSize];
	// Init board
	for (int i = 0; i < boardSize; i++)
		vBoard[i] = new char[3];

	for (int i = 0; i < boardSize; i++)
	{
		switch (board[i])
		{
		case 0:
			vBoard[i][0] = ' ';
			vBoard[i][1] = ' ';
			break;
		case 1:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '1';
			break;
		case 2:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '2';
			break;
		case 3:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '3';
			break;
		case 4:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '4';
			break;
		case 5:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '5';
			break;
		case 6:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '6';
			break;
		case 7:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '7';
			break;
		case 8:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '8';
			break;
		case 9:
			vBoard[i][0] = ' ';
			vBoard[i][1] = '9';
			break;
		case 10:
			vBoard[i][0] = '1';
			vBoard[i][1] = '0';
			break;
		case 11:
			vBoard[i][0] = '1';
			vBoard[i][1] = '1';
			break;
		case 12:
			vBoard[i][0] = '1';
			vBoard[i][1] = '2';
			break;
		case 13:
			vBoard[i][0] = '1';
			vBoard[i][1] = '3';
			break;
		case 14:
			vBoard[i][0] = '1';
			vBoard[i][1] = '4';
			break;
		case 15:
			vBoard[i][0] = '1';
			vBoard[i][1] = '5';
			break;
		default:
			vBoard[i][0] = 'N';
			vBoard[i][1] = 'N';
			break;
		}

		vBoard[i][2] = '\0';
	}

	return vBoard;
	delete[] vBoard;
}
void setBoardSize(int size)
{
	boardSize = size;
}
bool canMove(int* board, int tile)
{
	if (tile < 1 || tile > boardSize - 1)
		return false;

	int tilePos = 0;
	for (int i = 0; i < boardSize; i++)
		if (board[i] == tile)
			tilePos = i;

	if (tilePos + 1 < boardSize && board[tilePos + 1] == 0)
		return true;
	else if (tilePos - 1 >= 0 && board[tilePos - 1] == 0)
		return true;
	else if (tilePos + (int)sqrt(boardSize) < boardSize && board[tilePos + (int)sqrt(boardSize)] == 0)
		return true;
	else if (tilePos - (int)sqrt(boardSize) < boardSize && board[tilePos - (int)sqrt(boardSize)] == 0)
		return true;

	return false;
}
void moveTile(int* board, int tile)
{
	int tilePos = 0, nullPos = 0;

	for (int i = 0; i < boardSize; i++)
	{
		if (board[i] == tile)
			tilePos = i;
		if (board[i] == 0)
			nullPos = i;
	}

	board[tilePos] = 0;
	board[nullPos] = tile;
}
bool isSolved(int* board)
{
	for (int i = 0, corNum = 1; i < boardSize - 1; i++, corNum++)
		if (board[i] != corNum)
			return false;

	return true;
}

bool askExit()
{
	while(true)
	{
		int choice;
		std::cout << "Do you want to play again?" << std::endl
			<< "1. Yes" << std::endl
			<< "2. No" << std::endl;
		std::cin >> choice;

		if (choice == 2)
			return true;
		else if (choice == 1)
			return false;
		else
			std::cout << "Invalid command!" << std::endl;
	}
}
int askBSize()
{
	while (true)
	{
		int choice;

		std::cout << "Enter prefered board size:" << std::endl
			<< "1. 8 (3 x 3)" << std::endl
			<< "2. 15 (4 x 4)" << std::endl;
		std::cin >> choice;

		if (choice == 1)
			return 9;
		else if (choice == 2)
			return 16;
		else
			std::cout << "Invalid command!" << std::endl;
	}

	return 16;
}
int askMixMode()
{
	while (true)
	{
		int choice;

		std::cout << "Choose mix mode:" << std::endl
			<< "1. Auto mix\n"
			<< "2. Manual mix\n";
		std::cin >> choice;

		if (choice == 1)
			return 0;
		else if (choice == 2)
			return 1;
		else
			std::cout << "Invalid choice!" << std::endl;
	}

	return 0;
}
int askSolveMode()
{
	while (true)
	{
		int choice;

		std::cout << "Choose the playing mode:\n"
			<< "1. You are solving\n"
			<< "2. Computer is solving\n";
		std::cin >> choice;

		if (choice == 1)
			return 0;
		else if (choice == 2)
			return 1;
		else
			std::cout << "Invalid choice!" << std::endl;
	}

	return 0;
}

int* solvePlayer(int*& board, char**& viewBoard)
{
	int* stats = new int[2]{};

	int startTime, endTime;
	int moves = 0;

	startTime = time(NULL);

	while (true)
	{
		system("cls");
		drawBoard(viewBoard);

		bool corrMove = false;
		int chosen_tile;
		do
		{
			std::cout << "Enter which tile to move: ";
			std::cin >> chosen_tile;

			if (canMove(board, chosen_tile))
				corrMove = true;
			else
				std::cout << "Unmovable/Invalid tile!" << std::endl;
		} while (!corrMove);

		moveTile(board, chosen_tile);
		viewBoard = setView(board);

		moves++;

		if (isSolved(board))
		{
			system("cls");

			drawBoard(viewBoard);
			std::cout << "\nCongrats! Puzzle solved!" << std::endl;

			break;
		}
	}

	endTime = time(NULL);

	stats[0] = endTime - startTime;
	stats[1] = moves;

	return stats;
	delete[] stats;
}

void play15Puzzle()
{
	bool exit = false;

	int* board;
	char** viewBoard;

	while (!exit)
	{
		srand(time(NULL));

		system("cls");
		setBoardSize(askBSize());

		board = getMixedBoard(askMixMode());
		viewBoard = setView(board);

		if (askSolveMode())
		{
			// Computer solves
			//solveComputer(board, viewBoard);
		}
		else
		{
			// Player solves
			int* stats = solvePlayer(board, viewBoard);

			std::cout
				<< "\nTime: " << stats[0] << " seconds" << std::endl
				<< "Moves: " << stats[1] << std::endl << std::endl;
		}

		exit = askExit();
	}
}

