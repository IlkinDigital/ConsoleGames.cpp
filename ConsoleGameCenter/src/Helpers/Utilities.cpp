#include "Utilities.h"

int randint(int left, int right)
{
	if (right == left)
		return right;

	return rand() % (right - left + 1) + left;
}

void getEnter(const char* text)
{
	std::cin.ignore();
	std::cout << text;
	std::cin.get();
}