#include "TicTacToe.h"

void drawBoard(char board[])
{
	char* space = new char[] {"\t\t\t"};
	std::cout
		<< "    +   +    " << std::endl
		<< "  " << board[0] << " | " << board[1] << " | " << board[2] << "  " << std::endl
		<< "+---+---+---+" << std::endl
		<< "  " << board[3] << " | " << board[4] << " | " << board[5] << "  " << std::endl
		<< "+---+---+---+" << std::endl
		<< "  " << board[6] << " | " << board[7] << " | " << board[8] << "  " << std::endl
		<< "    +   +    " << std::endl;
}

bool checkWin(char board[], char playChar)
{
	return (board[0] == board[1] && board[0] == board[2] && board[0] == playChar) || 
		(board[3] == board[4] && board[3] == board[5] && board[3] == playChar) ||
		(board[6] == board[7] && board[6] == board[8] && board[6] == playChar) || 
		(board[0] == board[3] && board[0] == board[6] && board[0] == playChar) ||
		(board[1] == board[4] && board[1] == board[7] && board[1] == playChar) || 
		(board[2] == board[5] && board[2] == board[8] && board[2] == playChar) ||
		(board[0] == board[4] && board[0] == board[8] && board[0] == playChar) || 
		(board[2] == board[4] && board[2] == board[6] && board[2] == playChar);
}

void bflip(bool& key)
{
	if (key)
		key = false;
	else
		key = true;
}

int promptMove(char board[], char name)
{
	int move;
	bool validMove = false;
	do
	{
		std::cout << name << "'s turn" << std::endl
			<< "Enter index (1-9): ";
		std::cin >> move;
		move--;

		if (move >= 0 && move < 9)
		{
			if (board[move] != ' ')
				std::cout << "\nSpace is used!\n" << std::endl;
			else
				validMove = true;
		}
		else
			std::cout << "\nIndex is invalid!\n" << std::endl;

	} while (!validMove);

	return move;
}

void playTTT()
{
	const int length = 9;
	bool exit = false, game_finished, key;
	int playIndex, playCounter;
	char playChar;

	while (!exit)
	{
		game_finished = false;
		key = false;
		playCounter = 0;
		char board[] = BOARD;

		while (!game_finished)
		{
			system("cls");

			drawBoard(board);

			// Prompt, set move and player char
			playChar = 'x' - (('x' - 'o') * key);
			playIndex = promptMove(board, playChar);

			// Record the move
			board[playIndex] = playChar;
			playCounter++;

			// Check for WINS and TIES
			if (checkWin(board, playChar))
			{
				system("cls");
				drawBoard(board);

				std::cout << playChar << " WINS!!!\n" << std::endl;
				game_finished = true;
			}
			else if (playCounter >= 9)
			{
				system("cls");
				drawBoard(board);

				std::cout << "TIE!\n" << std::endl;
				game_finished = true;
			}

			bflip(key);
		}

		exit = askExit();
	}
}