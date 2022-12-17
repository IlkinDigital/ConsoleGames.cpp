#include "Battleship.h"


int main()
{
	bool exit = false;

	initGame();

	while (!exit)
	{
		int gameMode, shootMode;

		system("cls");

		gameMode = askGM();
		shootMode = askSM();

		if (gameMode == 1)
		{
			PlayerVsComputer(shootMode);
		}
		else
		{
			ComputerVsComputer(shootMode, "USA", "RUSSIA");
		}

		exit = askExit();
	}

	return 0;
}