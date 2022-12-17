#include "tictactoe.h"

void drawBoard(char board[])
{
	std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl
		<< "-----------" << std::endl
		<< " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl
		<< "-----------" << std::endl
		<< " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;
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
		cout << name << "'s turn" << endl
			<< "Enter index (1-9): ";
		cin >> move;
		move--;

		if (move >= 0 && move < 9)
		{
			if (board[move] != ' ')
				cout << "Space is used!" << endl;
			else
				validMove = true;
		}
		else
			cout << "Index is not valid!" << endl;

	} while (!validMove);

	return move;
}

bool askExit()
{
	int choice;
	do
	{
		cout << "\nDo you want to play again?" << endl
			<< "1. Yes" << endl
			<< "2. No" << endl;
		cin >> choice;

		if (choice < 1 || choice > 2)
			cout << "Invalid command!" << endl;
		
	} while (choice < 1 || choice > 2);

	return choice - 1;
}

void playRawTTT()
{
	const int length = 9;
	bool exit = false, game_finished, canPlay;
	int pturn, playIndex, playCounter;
	char playChar;

	cout << "Welcome to Ilkin's tic tac toe game!" << endl;

	while (!exit)
	{
		game_finished = false;
		playCounter = 0;
		pturn = 0;
		char board[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

		while (!game_finished)
		{
			// Draw Board
			cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
			cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
			cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;

			canPlay = false;
			if (pturn == 0)
			{
				do
				{
					cout << "Player 1's turn" << endl
						<< "Enter index: ";
					cin >> playIndex;

					if (playIndex > 0 && playIndex < length + 1)
					{
						if (board[playIndex - 1] != ' ')
							cout << "Space is used!" << endl;
						else
							canPlay = true;
					}
					else
						cout << "Index is not on the board!" << endl;

				} while (!canPlay);

				playChar = 'x';
				pturn++;
			}
			else
			{
				do
				{
					cout << "Player 2's turn" << endl
						<< "Enter index: ";
					cin >> playIndex;

					if (playIndex > 0 && playIndex < length + 1)
					{
						if (board[playIndex - 1] != ' ')
							cout << "Space is used!" << endl;
						else
							canPlay = true;
					}
					else
						cout << "Index is not on the board!" << endl;

				} while (!canPlay);

				playChar = 'o';
				pturn--;
			}

			board[playIndex - 1] = playChar;
			playCounter++;

			// Check for WINS or TIES
			if ((board[0] == board[1] && board[0] == board[2] && board[0] != ' ') || (board[3] == board[4] && board[3] == board[5] && board[3] != ' ') ||
				(board[6] == board[7] && board[6] == board[8] && board[6] != ' ') || (board[0] == board[3] && board[0] == board[6] && board[0] != ' ') ||
				(board[1] == board[4] && board[1] == board[7] && board[1] != ' ') || (board[2] == board[5] && board[2] == board[8] && board[2] != ' ') ||
				(board[0] == board[4] && board[0] == board[8] && board[0] != ' ') || (board[2] == board[4] && board[2] == board[6] && board[2] != ' '))
			{
				// Draw Board
				cout << " " << board[0] << " | " << board[1] << " | " << board[2] << endl;
				cout << " " << board[3] << " | " << board[4] << " | " << board[5] << endl;
				cout << " " << board[6] << " | " << board[7] << " | " << board[8] << endl;

				if (playChar == 'x')
					cout << "\nPlayer 1 WINS!!!" << endl;
				else
					cout << "\nPlayer 2 WINS!!!" << endl;
				game_finished = true;
			}
			else if (playCounter >= 9)
			{
				cout << "TIE!" << endl;
				game_finished = true;
			}
		}

		// Ask for restart
		int choice;
		do
		{
			cout << "\nDo you want to play again?" << endl
				<< "1. Yes" << endl
				<< "2. No" << endl;
			cin >> choice;
			if (choice == 1)
				exit = false;
			else if (choice == 2)
				exit = true;
			else
				cout << "Incorrect command!" << endl;
		} while (choice < 1 || choice > 2);
	}
}