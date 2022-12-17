#include "Puzzle.h"


int main()
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
				<< "\nTime: " << stats[0]  << " seconds" << std::endl
				<< "Moves: " << stats[1] << std::endl << std::endl;
		}

		exit = askExit();
	}

	return 0;
}