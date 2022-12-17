#include "Memory.h"


int main()
{
	int size;

	int totTurns = 0;
	int corrTurns = 0;
	int timeStart, timeEnd;

	bool finished = false;

	srand(time(NULL));

	/* Gameplay */
	/* START */
	size = askSize();

	char** itemsBoard = initBoardItems(size);
	char** frontBoard = initFront(size);

	timeStart = time(NULL);

	while (true)
	{
		system("cls");
		drawBoard(frontBoard, size);

		// Win Check
		if (corrTurns == size * size)
		{
			timeEnd = time(NULL);

			std::cout << "\nYou WON! You found all of the hidden pairs!" << std::endl;
			std::cout << "Press ENTER to finish the game...";
			std::cin.get();
			break;
		}

		int* fc_coords = new int[2];
		fc_coords = askCoords(itemsBoard, frontBoard, size);
		turnOver(fc_coords, frontBoard, itemsBoard);
		totTurns++;

		drawBoard(frontBoard, size);

		int* sc_coords = new int[2];
		sc_coords = askCoords(itemsBoard, frontBoard, size);
		turnOver(sc_coords, frontBoard, itemsBoard);
		totTurns++;

		drawBoard(frontBoard, size);

		if (itemsBoard[fc_coords[0]][fc_coords[1]] == itemsBoard[sc_coords[0]][sc_coords[1]])
		{
			Beep(329, 300);
			Beep(493, 300);
			Beep(698, 300);
			Beep(640, 500);

			std::cout << "\nThey match!\n" << std::endl;
			removeCard(fc_coords, frontBoard);
			removeCard(sc_coords, frontBoard);

			corrTurns += 2;

			std::cin.ignore();
			std::cout << "Press ENTER to remove these cards...";
			std::cin.get();
		}
		else
		{
			Beep(600, 600);

			std::cout << "\nThey don't match!\n" << std::endl;
			turnOver(fc_coords, frontBoard);
			turnOver(sc_coords, frontBoard);

			std::cin.ignore();
			std::cout << "Press ENTER to turn these cards over...";
			std::cin.get();
		}
	}

	std::cout
		<< "\nStats:" << std::endl
		<< "Total card turns: " << totTurns << std::endl
		<< "Total time spent: " << timeEnd - timeStart << " seconds" << std::endl;

	/* END */ 
	return 0;
}