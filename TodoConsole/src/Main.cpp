#include "TodoList.h"


int main()
{
	struct tm nowLocal;

	time_t currUTime = time(NULL);

	localtime_s(&nowLocal, &currUTime);

	Date date = currentDate();

	std::cout << date.year << " " << date.month << " " << date.day << " " << date.minute << " " << date.second << std::endl;

	std::cout << floatify(date);

	return 0;
}