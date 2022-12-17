#include "Battleship.h"


void initGame()
{
	srand(time(NULL));
}

char lower(char letter)
{
	if (letter >= 'Z' && letter <= 'A')
		letter = letter + ('a' - 'A');
	return letter;
}

void manualArrange(char board[row][col])
{
	int ships[5][3] = { { carrier, 5, false },
						{ bship, 4, false },
						{ destroyer, 3, false },
						{ submarine, 3, false },
						{ pBoat, 2, false } };

	for (int n = 0; n < 5; n++)
	{
		system("cls");
		std::cout << "Your board:" << std::endl;
		drawBoard(board);
		drawShips(ships);

		// 1 - up, 2 - down, 3 - right, 4 - left
		switch (n)
		{
		case 0:
			std::cout << "1. Place Carrier(size: 5)" << std::endl;
			break;
		case 1:
			std::cout << "2. Place Battleship(size: 4)" << std::endl;
			break;
		case 2:
			std::cout << "3. Place Destroyer(size: 3)" << std::endl;
			break;
		case 3:
			std::cout << "4. Place Submarine(size: 3)" << std::endl;
			break;
		case 4:
			std::cout << "5. Place Patrol Boat(size: 2)" << std::endl;
			break;
		default:
			break;
		}

		int direction = askDirection();

		int* edgeCoords = askEdgeCoords(board, direction, ships[n][1]);

		if (direction == 1)
		{
			// Up
			for (int i = edgeCoords[0]; i > edgeCoords[0] - ships[n][1]; i--)
				board[i][edgeCoords[1]] = (char)ships[n][0];
		}
		else if (direction == 2)
		{
			// Down
			for (int i = edgeCoords[0]; i < edgeCoords[0] + ships[n][1]; i++)
				board[i][edgeCoords[1]] = (char)ships[n][0];
		}
		else if (direction == 3)
		{
			// Right
			for (int j = edgeCoords[1]; j < edgeCoords[1] + ships[n][1]; j++)
				board[edgeCoords[0]][j] = (char)ships[n][0];
		}
		else if (direction == 4)
		{
			// Left
			for (int j = edgeCoords[1]; j > edgeCoords[1] - ships[n][1]; j--)
				board[edgeCoords[0]][j] = (char)ships[n][0];
		}
		else
			n--;

		ships[n][2] = true;
	}

	drawBoard(board);
}

void autoArrange(char board[row][col])
{
	int ships[5][3] = { { carrier, 5, false },
						{ bship, 4, false },
						{ destroyer, 3, false },
						{ submarine, 3, false },
						{ pBoat, 2, false } };

	for (int n = 0; n < 5; n++)
	{
		int r, c, dir;

		while (true)
		{
			r = randint(0, 9);
			c = randint(0, 9);

			dir = randint(1, 4);

			if (!doesCrossBorder(board, r, c, dir, ships[n][1]))
				if (!doesOverlap(board, r, c, dir, ships[n][1]))
				{
					placeShip(board, r, c, dir, ships[n][1], ships[n][0]);
					break;
				}
		}
	}
}

void initBoard(char b[row][col], char symbol)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			b[i][j] = symbol;
}

void drawBoard(char b[row][col])
{
	std::cout
		<< "    " << " 1  " << " 2  " << " 3  " << " 4  " << " 5  " << " 6  " << " 7  " << " 8  " << " 9  " << " 10  " << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " a | " << b[0][0] << " | " << b[0][1] << " | " << b[0][2] << " | " << b[0][3] << " | " << b[0][4] << " | " << b[0][5] << " | " << b[0][6] << " | " << b[0][7] << " | " << b[0][8] << " | " << b[0][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " b | " << b[1][0] << " | " << b[1][1] << " | " << b[1][2] << " | " << b[1][3] << " | " << b[1][4] << " | " << b[1][5] << " | " << b[1][6] << " | " << b[1][7] << " | " << b[1][8] << " | " << b[1][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " c | " << b[2][0] << " | " << b[2][1] << " | " << b[2][2] << " | " << b[2][3] << " | " << b[2][4] << " | " << b[2][5] << " | " << b[2][6] << " | " << b[2][7] << " | " << b[2][8] << " | " << b[2][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " d | " << b[3][0] << " | " << b[3][1] << " | " << b[3][2] << " | " << b[3][3] << " | " << b[3][4] << " | " << b[3][5] << " | " << b[3][6] << " | " << b[3][7] << " | " << b[3][8] << " | " << b[3][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " e | " << b[4][0] << " | " << b[4][1] << " | " << b[4][2] << " | " << b[4][3] << " | " << b[4][4] << " | " << b[4][5] << " | " << b[4][6] << " | " << b[4][7] << " | " << b[4][8] << " | " << b[4][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " f | " << b[5][0] << " | " << b[5][1] << " | " << b[5][2] << " | " << b[5][3] << " | " << b[5][4] << " | " << b[5][5] << " | " << b[5][6] << " | " << b[5][7] << " | " << b[5][8] << " | " << b[5][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " g | " << b[6][0] << " | " << b[6][1] << " | " << b[6][2] << " | " << b[6][3] << " | " << b[6][4] << " | " << b[6][5] << " | " << b[6][6] << " | " << b[6][7] << " | " << b[6][8] << " | " << b[6][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " h | " << b[7][0] << " | " << b[7][1] << " | " << b[7][2] << " | " << b[7][3] << " | " << b[7][4] << " | " << b[7][5] << " | " << b[7][6] << " | " << b[7][7] << " | " << b[7][8] << " | " << b[7][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " i | " << b[8][0] << " | " << b[8][1] << " | " << b[8][2] << " | " << b[8][3] << " | " << b[8][4] << " | " << b[8][5] << " | " << b[8][6] << " | " << b[8][7] << " | " << b[8][8] << " | " << b[8][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl
		<< " j | " << b[9][0] << " | " << b[9][1] << " | " << b[9][2] << " | " << b[9][3] << " | " << b[9][4] << " | " << b[9][5] << " | " << b[9][6] << " | " << b[9][7] << " | " << b[9][8] << " | " << b[9][9] << " |" << std::endl
		<< "   " << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---" << "+---+" << std::endl;
}
void drawShips(int ships[5][3])
{
	std::cout << "Ships left: " << std::endl;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < ships[i][1]; j++)
			if (!ships[i][2])
				std::cout << (char)ships[i][0];
		if (!ships[i][2])
			std::cout << std::endl;
	}
}

int askArrType()
{
	int choice;
	do
	{
		std::cout << "Arrangement types\n"
			<< "1. Manual arrange\n"
			<< "2. Auto arrange(random)\n";
		std::cin >> choice;

		if (choice == 1)
			return 0;
		else if (choice == 2)
			return 1;
		else
			std::cout << "Invalid choice!" << std::endl;
	} while (choice < 1 || choice > 2);

	return 1;
}
bool askArranged()
{
	int choice;
	do
	{
		std::cout
			<< "1. Rearrange ships\n"
			<< "2. Keep ships\n";
		std::cin >> choice;

		if (choice == 1)
			return false;
		else if (choice == 2)
			return true;
		else
			std::cout << "Invalid choice!" << std::endl;
	} while (choice < 1 || choice > 2);

	return false;
}

int askGM()
{
	while (true)
	{
		int gm;

		std::cout << "Choose game mode: " << std::endl
			<< "1. Player vs Computer" << std::endl
			<< "2. Computer vs Computer" << std::endl;
		std::cin >> gm;

		if (gm == 1 || gm == 2)
			return gm;
		else
			std::cout << "Invalid choice!" << std::endl;
	}
	return 1;
}

int askSM()
{
	while (true)
	{
		int sm;

		std::cout << "Choose Bot's shooting mode" << std::endl
			<< "1. Dummy shooting (random shooting)" << std::endl
			<< "2. Strategic shooting" << std::endl;
		std::cin >> sm;

		if (sm == 1 || sm == 2)
			return sm;
		else
			std::cout << "Invalid choice!" << std::endl;
	}
	return 0;
}

int askDirection()
{
	while (true)
	{
		int d;

		std::cout << "Enter direction (1-up, 2-down, 3-right, 4-left): ";
		std::cin >> d;

		if (1 <= d && d <= 4)
			return d;
		else
			std::cout << "Invalid direction!" << std::endl;
	}

	return 1;
}

int* askEdgeCoords(char b[row][col], int direction, int shipSize)
{
	int coords[2];

	bool isCorrect = false;
	char lc;
	int ilc;
	int nc;
	do
	{
		std::cout << "Enter coords with space (ex: C 8): ";
		std::cin >> lc;
		std::cin >> nc;

		lower(lc);
		if (nc >= 1 && nc <= row && lc <= 'j' && lc >= 'a')
		{
			ilc = lc - 'a';
			if (!doesCrossBorder(b, ilc, nc - 1, direction, shipSize))
			{
				if (!doesOverlap(b, ilc, nc - 1, direction, shipSize))
					isCorrect = true;
				else
					std::cout << "Ship CANNOT overlap another ship!" << std::endl;
			}
			else
				std::cout << "Ship CANNOT be placed out of border!" << std::endl;
		}
		else
			std::cout << "Ship CANNOT be placed out of border!" << std::endl;

	} while (!isCorrect);

	coords[0] = ilc;
	coords[1] = nc - 1;

	return coords;
}

int* getCoords(char viewBoard[row][col])
{
	int* coords = new int[2]{};
	
	bool isCorrect = false;
	char lc;
	int ilc;
	int nc;
	do
	{
		std::cout << "Enter coords with space (ex: a 3): ";
		std::cin >> lc;
		std::cin >> nc;

		lc = lower(lc);
		if (nc >= 1 && nc <= 10 && lc <= 'j' && lc >= 'a')
		{
			ilc = lc - 'a';
			if (viewBoard[ilc][nc - 1] == initSymb)
				isCorrect = true;
			else
				std::cout << "You can't shoot at the same place again!" << std::endl;
		}
		else
			std::cout << "Invalid coordinates!" << std::endl;

	} while (!isCorrect);

	coords[0] = ilc;
	coords[1] = nc - 1;

	return coords;
	delete[] coords;
}

int getSSize(int index)
{
	switch (index)
	{
	case 1:
		return 5;
	case 2:
		return 4;
	case 3:
	case 4:
		return 3;
	case 5:
		return 2;
	default:
		break;
	}

	return 0;
}

bool canShoot(int coords[], char viewBoard[row][col])
{
	if (viewBoard[coords[0]][coords[1]] == initSymb)
		return true;

	return false;
}

int getPossibleMoves(int coords[], char viewBoard[row][col])
{
	int result = 0;

	if (coords[0] - 1 >= 0)
		if (viewBoard[coords[0] - 1][coords[1]] == initSymb)
			result++;	
	if (coords[0] + 1 < 10)
		if (viewBoard[coords[0] + 1][coords[1]] == initSymb)
			result++;	
	if (coords[1] - 1 >= 0)
		if (viewBoard[coords[0]][coords[1] - 1] == initSymb)
			result++;	
	if (coords[0] + 1 < 10)
		if (viewBoard[coords[0]][coords[1] + 1] == initSymb)
			result++;

	return result;
}

char* getAroundDirections(int coords[], char viewBoard[row][col])
{
	char* directions = new char[4]{};

	int i = 0;

	if (coords[0] - 1 >= 0)
		if (viewBoard[coords[0] - 1][coords[1]] == initSymb)
			directions[i++] = 't';
	if (coords[0] + 1 < 10)
		if (viewBoard[coords[0] + 1][coords[1]] == initSymb)
			directions[i++] = 'b';
	if (coords[1] - 1 >= 0)
		if (viewBoard[coords[0]][coords[1] - 1] == initSymb)
			directions[i++] = 'l';
	if (coords[0] + 1 < 10)
		if (viewBoard[coords[0]][coords[1] + 1] == initSymb)
			directions[i++] = 'r';

	return directions;
	delete[] directions;
}

int* shoot(int coords[], char viewBoard[row][col], char board[row][col])
{
	int r = coords[0];
	int c = coords[1];

	int* stats = new int[4]{};

	stats[2] = r;
	stats[3] = c;

	if (board[r][c] == initSymb)
	{
		// Miss
		board[r][c] = missSymb;
		viewBoard[r][c] = missSymb;

		stats[0] = false;
		stats[1] = 0;
	}
	else
	{
		// Hit
		char ship = board[r][c];

		viewBoard[r][c] = hitSymb;
		board[r][c] = hitSymb;

		stats[0] = true;
		switch (ship)
		{
		case 'C':
			stats[1] = 1;
			break;
		case 'B':
			stats[1] = 2;
			break;
		case 'D':
			stats[1] = 3;
			break;
		case 'S':
			stats[1] = 4;
			break;
		case 'P':
			stats[1] = 5;
			break;
		default:
			break;
		}
	}

	return stats;
	delete[] stats;
}

int* dummyShoot(char viewBoard[row][col], char board[row][col])
{
	int x, y;
	do
	{
		y = randint(0, 9);
		x = randint(0, 9);
	} while (viewBoard[y][x] != initSymb);
	
	int coords[2] = { y, x };

	int* stats = shoot(coords, viewBoard, board);

	return stats;
}

int* smartShoot1(char viewBoard[row][col], char board[row][col])
{
	static bool shouldHunt = true;
	static bool isGoingAround = false;
	static bool isDirProductive = false;

	static int prevShot[2]{};
	static int origShot[2]{};

	static int shotCounter[5]{};
	static int shipSize = 0;
	static int shipIndex = 0;

	// h - horizontal, v - vertical
	static char goDirection;
	static char subDir;

	int* stats; 


	if (shouldHunt)
	{
		stats = dummyShoot(viewBoard, board);

		if (stats[0])
		{
			shipIndex = stats[1] - 1;

			shipSize = getSSize(stats[1]);
			shotCounter[shipIndex]++;

			prevShot[0] = stats[2];
			prevShot[1] = stats[3];

			origShot[0] = prevShot[0];
			origShot[1] = prevShot[1];

			if (shotCounter[shipIndex] != shipSize)
			{
				shouldHunt = false;
				isGoingAround = true;
			}
		}
	}
	else
	{
		if (isGoingAround)
		{
			int possMoves = getPossibleMoves(origShot, viewBoard);
			char* aroundDir = getAroundDirections(origShot, viewBoard);

			char direction = aroundDir[randint(0, possMoves - 1)];

			switch (direction)
			{
			case 't':
				prevShot[0] = origShot[0] - 1;
				prevShot[1] = origShot[1];
				break;
			case 'b':
				prevShot[0] = origShot[0] + 1;
				prevShot[1] = origShot[1];
				break;
			case 'r':
				prevShot[0] = origShot[0];
				prevShot[1] = origShot[1] + 1;
				break;
			case 'l':
				prevShot[0] = origShot[0];
				prevShot[1] = origShot[1] - 1;
				break;
			default:
				break;
			}

			stats = shoot(prevShot, viewBoard, board);

			// stats[0] --> did hit?
			if (stats[0])
			{
				if (direction == 't' || direction == 'b')
					goDirection = 'h';
				else
					goDirection = 'v';

				shipIndex = stats[1] - 1;
				shipSize = getSSize(stats[1]);

				shotCounter[shipIndex]++;

				isGoingAround = false;

				// Check if ship is destroyed
				if (shotCounter[shipIndex] == shipSize)
					shouldHunt = true;
				else
				{
					isDirProductive = true;
					subDir = direction;
				}
			}
		}
		else
		{
			int coords[2] = { prevShot[0], prevShot[1] };

			int changeIndex;
			char dirDecrement, dirIncrement;

			if (goDirection == 'h')
			{
				changeIndex = 0;
				dirDecrement = 't';
				dirIncrement = 'b';
			}
			else
			{
				changeIndex = 1;
				dirDecrement = 'l';
				dirIncrement = 'r';
			}

			if (isDirProductive)
			{
				if (subDir == dirDecrement)
					coords[changeIndex]--;
				else
					coords[changeIndex]++;

				if (canShoot(coords, viewBoard))
				{
					stats = shoot(coords, viewBoard, board);

					isDirProductive = stats[0];
					if (!isDirProductive)
					{
						subDir = subDir == dirDecrement ? dirIncrement : dirDecrement;
						coords[changeIndex] = origShot[changeIndex];
					}
					else
						shotCounter[stats[1] - 1]++;
				}
				else
				{
					subDir = subDir == dirDecrement ? dirIncrement : dirDecrement;

					if (subDir == dirDecrement)
						coords[changeIndex] = origShot[changeIndex] - 1;
					else
						coords[changeIndex] = origShot[changeIndex] + 1;

					stats = shoot(coords, viewBoard, board);

					isDirProductive = false;
				}
			}
			else
			{
				if (subDir == dirDecrement)
					coords[changeIndex]--;
				else
					coords[changeIndex]++;

				stats = shoot(coords, viewBoard, board);
				shotCounter[stats[1] - 1]++;
			}

			prevShot[0] = coords[0];
			prevShot[1] = coords[1];

			shipSize = getSSize(stats[1]);

			if (shotCounter[stats[1] - 1] == shipSize)
			{
				shouldHunt = true;
				isGoingAround = false;
				isDirProductive = false;
			}
		}
	}

	return stats;
}

int* smartShoot2(char viewBoard[row][col], char board[row][col])
{
	static bool shouldHunt = true;
	static bool isGoingAround = false;
	static bool isDirProductive = false;

	static int prevShot[2]{};
	static int origShot[2]{};

	static int shotCounter[5]{};
	static int shipSize = 0;
	static int shipIndex = 0;

	// h - horizontal, v - vertical
	static char goDirection;
	static char subDir;

	int* stats;


	if (shouldHunt)
	{
		stats = dummyShoot(viewBoard, board);

		if (stats[0])
		{
			shipIndex = stats[1] - 1;

			shipSize = getSSize(stats[1]);
			shotCounter[shipIndex]++;

			prevShot[0] = stats[2];
			prevShot[1] = stats[3];

			origShot[0] = prevShot[0];
			origShot[1] = prevShot[1];

			if (shotCounter[shipIndex] != shipSize)
			{
				shouldHunt = false;
				isGoingAround = true;
			}
		}
	}
	else
	{
		if (isGoingAround)
		{
			int possMoves = getPossibleMoves(origShot, viewBoard);
			char* aroundDir = getAroundDirections(origShot, viewBoard);

			char direction = aroundDir[randint(0, possMoves - 1)];

			switch (direction)
			{
			case 't':
				prevShot[0] = origShot[0] - 1;
				prevShot[1] = origShot[1];
				break;
			case 'b':
				prevShot[0] = origShot[0] + 1;
				prevShot[1] = origShot[1];
				break;
			case 'r':
				prevShot[0] = origShot[0];
				prevShot[1] = origShot[1] + 1;
				break;
			case 'l':
				prevShot[0] = origShot[0];
				prevShot[1] = origShot[1] - 1;
				break;
			default:
				break;
			}

			stats = shoot(prevShot, viewBoard, board);

			// stats[0] --> did hit?
			if (stats[0])
			{
				if (direction == 't' || direction == 'b')
					goDirection = 'h';
				else
					goDirection = 'v';

				shipIndex = stats[1] - 1;
				shipSize = getSSize(stats[1]);

				shotCounter[shipIndex]++;

				isGoingAround = false;

				// Check if ship is destroyed
				if (shotCounter[shipIndex] == shipSize)
					shouldHunt = true;
				else
				{
					isDirProductive = true;
					subDir = direction;
				}
			}
		}
		else
		{
			int coords[2] = { prevShot[0], prevShot[1] };

			int changeIndex;
			char dirDecrement, dirIncrement;

			if (goDirection == 'h')
			{
				changeIndex = 0;
				dirDecrement = 't';
				dirIncrement = 'b';
			}
			else
			{
				changeIndex = 1;
				dirDecrement = 'l';
				dirIncrement = 'r';
			}

			if (isDirProductive)
			{
				if (subDir == dirDecrement)
					coords[changeIndex]--;
				else
					coords[changeIndex]++;

				if (canShoot(coords, viewBoard))
				{
					stats = shoot(coords, viewBoard, board);

					isDirProductive = stats[0];
					if (!isDirProductive)
					{
						subDir = subDir == dirDecrement ? dirIncrement : dirDecrement;
						coords[changeIndex] = origShot[changeIndex];
					}
					else
						shotCounter[stats[1] - 1]++;
				}
				else
				{
					subDir = subDir == dirDecrement ? dirIncrement : dirDecrement;

					if (subDir == dirDecrement)
						coords[changeIndex] = origShot[changeIndex] - 1;
					else
						coords[changeIndex] = origShot[changeIndex] + 1;

					stats = shoot(coords, viewBoard, board);

					isDirProductive = false;
				}
			}
			else
			{
				if (subDir == dirDecrement)
					coords[changeIndex]--;
				else
					coords[changeIndex]++;

				stats = shoot(coords, viewBoard, board);
				shotCounter[stats[1] - 1]++;
			}

			prevShot[0] = coords[0];
			prevShot[1] = coords[1];

			shipSize = getSSize(stats[1]);

			if (shotCounter[stats[1] - 1] == shipSize)
			{
				shouldHunt = true;
				isGoingAround = false;
				isDirProductive = false;
			}
		}
	}

	return stats;
}

bool doesOverlap(char vb[row][col], int r, int c, int direction, int shipSize)
{
	switch (direction)
	{
	case 1:
		for (int i = r; i > r - shipSize; i--)
			if (vb[i][c] != initSymb)
				return true;
		break;
	case 2:
		for (int i = r; i < r + shipSize; i++)
			if (vb[i][c] != initSymb)
				return true;
		break;
	case 3:
		for (int j = c; j < c + shipSize; j++)
			if (vb[r][j] != initSymb)
				return true;
		break;
	case 4:
		for (int j = c; j > c - shipSize; j--)
			if (vb[r][j] != initSymb)
				return true;
		break;
	default:
		return true;
	}

	return false;
}

bool doesCrossBorder(char vb[row][col], int r, int c, int direction, int shipSize)
{
	switch (direction)
	{
	case 1:
		for (int i = r; i > r - shipSize; i--)
			if (i >= row || i < 0)
				return true;
		break;
	case 2:
		for (int i = r; i < r + shipSize; i++)
			if (i >= row || i < 0)
				return true;
		break;
	case 3:
		for (int j = c; j < c + shipSize; j++)
			if (j >= col || j < 0)
				return true;
		break;
	case 4:
		for (int j = c; j > c - shipSize; j--)
			if (j >= col || j < 0)
				return true;
		break;
	default:
		return true;
	}

	return false;
}

void placeShip(char b[row][col], int r, int c, int direction, int shipSize, char shipSymb)
{
	switch (direction)
	{
	case 1:
		for (int i = r; i > r - shipSize; i--)
			b[i][c] = (char)shipSymb;
		break;
	case 2:
		for (int i = r; i < r + shipSize; i++)
			b[i][c] = (char)shipSymb;
		break;
	case 3:
		for (int j = c; j < c + shipSize; j++)
			b[r][j] = (char)shipSymb;
		break;
	case 4:
		for (int j = c; j > c - shipSize; j--)
			b[r][j] = (char)shipSymb;
		break;
	default:
		break;
	}
}

void PlayerVsComputer(int shootMode)
{
	int* (*botShoot)(char[row][col], char[row][col]);
	if (shootMode == 1)
		botShoot = dummyShoot;
	else
		botShoot = smartShoot1;

	bool arranged = false, game = false;

	// Player's visible boards
	char playerBoard[row][col];
	char vEnemyBoard[row][col];

	// Enemy's visible boards
	char enemyBoard[row][col];
	char vPlayerBoard[row][col];

	/* START */

	// Initialization phase
	initBoard(playerBoard, initSymb);
	initBoard(vEnemyBoard, initSymb);
	initBoard(enemyBoard, initSymb);
	initBoard(vPlayerBoard, initSymb);

	int playerHits = 0, enemyHits = 0;

	// Arrange Phase
	autoArrange(enemyBoard);

	int aType = askArrType();

	if (aType == 0)
	{
		int choice;
		do
		{
			initBoard(playerBoard, initSymb);
			manualArrange(playerBoard);
			do
			{
				std::cout << "Do you want to keep this layout?" << std::endl
					<< "1. Yes" << std::endl
					<< "2. No" << std::endl;
				std::cin >> choice;

				if (choice < 1 || choice > 2)
					std::cout << "Invalid choice!" << std::endl;
			} while (choice < 1 || choice > 2);
		} while (choice != 1);
	}
	else
	{
		while (!arranged)
		{
			initBoard(playerBoard, initSymb);
			autoArrange(playerBoard);

			system("cls");
			std::cout << "Randomly arranged board: " << std::endl;
			drawBoard(playerBoard);

			arranged = askArranged();
		}
	}

	getEnter("Press enter to start the game...");

	// Game phase
	while (!game)
	{
		// Player's Turn
		system("cls");
		std::cout << "Your board:" << std::endl;
		drawBoard(playerBoard);
		std::cout << "Your shoots board:" << std::endl;
		drawBoard(vEnemyBoard);

		int* coords = getCoords(vEnemyBoard);

		int* pStats = shoot(coords, vEnemyBoard, enemyBoard);

		system("cls");
		std::cout << "Your board:" << std::endl;
		drawBoard(playerBoard);
		std::cout << "Your shoots board:" << std::endl;
		drawBoard(vEnemyBoard);

		if (pStats[0])
		{
			std::cout << "You hit ";
			switch (pStats[1])
			{
			case 1:
				std::cout << "Carrier(size 5)!" << std::endl;
				break;
			case 2:
				std::cout << "Battleship(size 4)!" << std::endl;
				break;
			case 3:
				std::cout << "Destroyer(size 3)!" << std::endl;
				break;
			case 4:
				std::cout << "Submarine(size 3)!" << std::endl;
				break;
			case 5:
				std::cout << "Patrol Boat(size 2)!" << std::endl;
				break;
			default:
				std::cout << "Error ship(size 0)!" << std::endl;
				break;
			}

			playerHits++;
		}
		else
			std::cout << "You missed!" << std::endl;

		// Bot's turn
		// TODO: bot's shoot

		getEnter("Press enter to continue to opponent's shot...");

		int* eStats = botShoot(vPlayerBoard, playerBoard);

		system("cls");
		std::cout << "Your board:" << std::endl;
		drawBoard(playerBoard);
		std::cout << "Your shoots board:" << std::endl;
		drawBoard(vEnemyBoard);

		if (eStats[0])
		{
			std::cout << "Opponent hit you!" << std::endl;
			enemyHits++;
		}
		else
			std::cout << "Opponent missed!" << std::endl;

		// Win check
		if (playerHits > enemyHits && playerHits == 17)
		{
			// Player Wins
			std::cout << "You WON! You destroyed all of the enemy ships!" << std::endl;
			game = true;
			getEnter("Press enter to finish game...");
		}
		else if (enemyHits > playerHits && enemyHits == 17)
		{
			// Bot wins
			std::cout << "You LOST! Opponent destroyed all of your ships!" << std::endl;
			game = true;
			getEnter("Press enter to finish game...");
		}
		else if (playerHits == 17 && enemyHits == 17)
		{
			// Tie
			std::cout << "Tie! You simultaneously destroyed each other xD!" << std::endl;
			game = true;
			getEnter("Press enter to finish game...");
		}
		else
		{
			std::cout << "Press enter to continue...";
			std::cin.get();
		}
	}

	/* END */
}

void ComputerVsComputer(int shootMode, const char* p1, const char* p2)
{
	int* (*bot1Shoot)(char[row][col], char[row][col]);
	int* (*bot2Shoot)(char[row][col], char[row][col]);
	if (shootMode == 1)
	{
		bot1Shoot = dummyShoot;
		bot2Shoot = dummyShoot;
	}
	else
	{
		bot1Shoot = smartShoot1;
		bot2Shoot = smartShoot2;
	}

	bool arranged = false, game = false;

	// Player's visible boards
	char bot1Board[row][col];
	char vBot2Board[row][col];

	// Enemy's visible boards
	char bot2Board[row][col];
	char vBot1Board[row][col];

	/* START */

	// Initialization phase
	initBoard(bot1Board, initSymb);
	initBoard(vBot2Board, initSymb);
	initBoard(bot2Board, initSymb);
	initBoard(vBot1Board, initSymb);

	int bot1Hits = 0, bot2Hits = 0;

	// Arrange Phase
	autoArrange(bot1Board);
	autoArrange(bot2Board);

	getEnter("Press enter to start the game...");

	// Game phase
	while (!game)
	{
		system("cls");
		std::cout << p1 << "'s board:" << std::endl;
		drawBoard(bot1Board);
		std::cout << p2 << "'s board:" << std::endl;
		drawBoard(bot2Board);

		std::cout << "Press enter to continue to player1's shot...";
		std::cin.ignore();

		// Bot1's turn

		int* bot1Stats = bot1Shoot(vBot2Board, bot2Board);

		system("cls");
		std::cout << p1 << "'s board:" << std::endl;
		drawBoard(bot1Board);
		std::cout << p2 << "'s board:" << std::endl;
		drawBoard(bot2Board);

		if (bot1Stats[0])
		{
			std::cout << p1 << " hit ";
			switch (bot1Stats[1])
			{
			case 1:
				std::cout << "Carrier(size 5)!" << std::endl;
				break;
			case 2:
				std::cout << "Battleship(size 4)!" << std::endl;
				break;
			case 3:
				std::cout << "Destroyer(size 3)!" << std::endl;
				break;
			case 4:
				std::cout << "Submarine(size 3)!" << std::endl;
				break;
			case 5:
				std::cout << "Patrol Boat(size 2)!" << std::endl;
				break;
			default:
				std::cout << "Error ship(size 0)!" << std::endl;
				break;
			}

			bot1Hits++;
		}
		else
			std::cout << p1 << " missed!" << std::endl;

		// Bot2's turn

		getEnter("Press enter to continue to player2's shot...");

		int* bot2Stats = bot2Shoot(vBot1Board, bot1Board);

		system("cls");
		std::cout << p1 << "'s board:" << std::endl;
		drawBoard(bot1Board);
		std::cout << p2 << "'s board:" << std::endl;
		drawBoard(bot2Board);

		if (bot2Stats[0])
		{
			std::cout << p2 << " hit ";
			switch (bot2Stats[1])
			{
			case 1:
				std::cout << "Carrier(size 5)!" << std::endl;
				break;
			case 2:
				std::cout << "Battleship(size 4)!" << std::endl;
				break;
			case 3:
				std::cout << "Destroyer(size 3)!" << std::endl;
				break;
			case 4:
				std::cout << "Submarine(size 3)!" << std::endl;
				break;
			case 5:
				std::cout << "Patrol Boat(size 2)!" << std::endl;
				break;
			default:
				std::cout << "Error ship(size 0)!" << std::endl;
				break;
			}

			bot2Hits++;
		}
		else
			std::cout << p2 << " missed!" << std::endl;

		// Win check
		if (bot1Hits > bot2Hits && bot1Hits == 17)
		{
			// Bot1 Wins
			std::cout << p1 << " has WON! " << p1 << " destroyed all of the enemy ships!" << std::endl;
			game = true;
			getEnter("Press enter to finish game...");
		}
		else if (bot2Hits > bot1Hits && bot2Hits == 17)
		{
			// Bot2 wins
			std::cout << p2 << " has WON! " << p2 << " destroyed all of the enemy ships!" << std::endl;
			game = true;
			getEnter("Press enter to finish game...");
		}
		else if (bot1Hits == 17 && bot2Hits == 17)
		{
			// Tie
			std::cout << "Tie! They destroyed each other at the same time xD!" << std::endl;
			game = true;
			getEnter("Press enter to finish game...");
		}
		else
		{
			std::cout << "Press enter to continue...";
			std::cin.get();
		}
	}
	/* END */
}

void playBattleship()
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
			PlayerVsComputer(shootMode);
		else
			ComputerVsComputer(shootMode, "Player 1", "Player 2");

		exit = askExit();
	}
}
