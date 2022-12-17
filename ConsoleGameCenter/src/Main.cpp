#include "Games/TicTacToe.h"
#include "Games/Battleship.h"
#include "Games/Puzzle.h"
#include "Games/Memory.h"

#include "Helpers/Prompts.h"
#include "Helpers/Utilities.h"

int main()
{
	int gameChoice;
	bool exit = false;

	srand(time(NULL));

	while (!exit)
	{
		system("cls");

		std::cout 
			<< "Welcome to Ilkin's Console Game Center!" << std::endl
			<< "Made as a final project for CS50x\n" << std::endl;

		gameChoice = askAction();

		if (gameChoice == 1)
			playTTT();
		else if (gameChoice == 2)
			playBattleship();
		else if (gameChoice == 3)
			play15Puzzle();
		else if (gameChoice == 4)
			playMemory();
		else
			exit = true;
		
		if (exit)
			getEnter("\nPress enter to exit the Game Center...");

	}
}