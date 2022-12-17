#include <iostream>
using namespace std;

#include "tictactoe.h"

int main()
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
			drawBoard(board);

			// Prompt, set move and player char
			playChar = 'x' - (('x' - 'o') * key);
			playIndex = promptMove(board, playChar);

			// Record the move
			board[playIndex] = playChar;
			playCounter++;

			// Check for WINS or TIES
			if (checkWin(board, playChar))
			{
				drawBoard(board);

				cout << playChar << " WINS!!!" << endl;
				game_finished = true;
			}
			else if (playCounter >= 9)
			{
				drawBoard(board);
				cout << "TIE!" << endl;
				game_finished = true;
			}

			bflip(key);
		}

		// Ask for restart of the game
		exit = askExit();
	}

	return 0;
}