#include "Prompts.h"

int askAction()
{
	while (true)
	{
		int choice;

		std::cout
			<< "What do you want to play or do:" << std::endl
			<< "1. Tic-Tac-Toe (2 players)" << std::endl
			<< "2. Battleship" << std::endl
			<< "3. 15 Puzzle" << std::endl
			<< "4. Memory game" << std::endl
			<< "5. Exit the Game Center" << std::endl;
		std::cin >> choice;

		if (choice >= 1 && choice <= 5)
			return choice;

		std::cout << "\nInvalid command!" << std::endl;
	}
}
bool askExit()
{
	while (true)
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