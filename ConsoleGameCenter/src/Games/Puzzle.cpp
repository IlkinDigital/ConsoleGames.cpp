#include "Puzzle.h"

int boardSize = 16;

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
int* getMixedBoard()
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
	int* stats = new int[3]{};

	bool exit = false;
	bool manualExit = false;

	int startTime, endTime;
	int moves = 0;

	startTime = time(NULL);

	while (!exit)
	{
		system("cls");
		drawBoard(viewBoard);

		bool corrMove = false;
		int chosen_tile;
		do
		{
			std::cout << "Enter which tile to move (0 to exit): ";
			std::cin >> chosen_tile;

			if (canMove(board, chosen_tile) || chosen_tile == 0)
				corrMove = true;
			else
				std::cout << "Unmovable/Invalid tile!" << std::endl;
		} while (!corrMove);

		if (chosen_tile == 0)
		{
			int choice;

			do
			{
				std::cout
					<< "Are you sure you want to exit the game?" << std::endl
					<< "1. Yes" << std::endl
					<< "2. No" << std::endl;
				std::cin >> choice;

				if (choice == 1)
				{
					exit = true;
					manualExit = true;
				}
				else if (choice != 2)
					std::cout << "Invalid command!" << std::endl;

			} while (choice < 1 || choice > 2);
		}
		else
		{
			moveTile(board, chosen_tile);
			viewBoard = setView(board);

			moves++;
		}

		if (isSolved(board))
		{
			system("cls");

			drawBoard(viewBoard);
			std::cout << "\nCongrats! Puzzle solved!" << std::endl;

			exit = true;
		}
	}

	endTime = time(NULL);

	stats[0] = !manualExit;
	stats[1] = endTime - startTime;
	stats[2] = moves;

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

		board = getMixedBoard();
		viewBoard = setView(board);

		// Player solves
		int* stats = solvePlayer(board, viewBoard);

		if (stats[0])
		{
			std::cout
				<< "\nTime: " << stats[1] << " seconds" << std::endl
				<< "Moves: " << stats[2] << std::endl << std::endl;

			exit = askExit();
		}
		else
			exit = true;
	}
}

