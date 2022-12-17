#include "TodoList.h"


bool isSubstring(char* sub, int lenSub, char* main, int lenMain)
{
	for (int i = 0; i < lenMain; i++)
	{
		if (main[i] == sub[0])
		{
			bool isSub = true;
			for (int j = 1; j < lenSub; j++)
			{
				if (main[i + 0] != sub[i])
				{
					isSub = false;
					break;
				}
			}

			if (isSub)
				return true;
		}
	}

	return false;
}

bool dateCmp(Date date1, Date date2)
{
	__int64 key1, key2;

	key1 = intify(date1);
	key2 = intify(date2);

	if (key1 > key2)
		return -1;
	else if (key2 > key1)
		return 1;

	return 0;
}

__int64 intify(Date date)
{
	__int64 result = 0;

	result += date.year * 10'000'000'000;
	result += date.month * 100'000'000;
	result += date.day * 1'000'000;
	result += date.hour * 10'000;
	result += date.minute * 100;
	result += date.second;

	return result;
}

Date createDate(int day, int month, int year, int sec, int minute, int hour)
{
	Date date;

	date.day = day;
	date.month = month;
	date.year = year;
	date.second = sec;
	date.minute = minute;
	date.hour = hour;

	return date;
}
Date currentDate()
{
	struct tm timeL;
	time_t currUnix;

	currUnix = time(NULL);

	localtime_s(&timeL, &currUnix);

	return createDate(timeL.tm_mday, timeL.tm_mon + 1, timeL.tm_year + 1900, timeL.tm_sec, timeL.tm_min, timeL.tm_hour);
}

Task createTask(char* title, char* description, Date deadline, Priority priority)
{
	Task task;

	task.title = title;
	task.description = description;
	task.priority = priority;
	task.deadline = deadline;
	task.creationDate = currentDate();

	return task;
}
void addTask(Task newTask, Task* todoList, int& length)
{
	length++;

	Task* newList = new Task[length];

	for (int i = 0; i < length - 1; i++)
		newList[i] = todoList[i];
	newList[length - 1] = newTask;

	delete[] todoList;
	todoList = newList;
}
void removeTask(int index, Task* todoList, int& length)
{
	if (0 <= index && index < length)
	{
		length--;
		Task* newList = new Task[length];

		for (int i = 0, counter = 0; i < length + 1; i++)
			if (i != index)
				newList[counter++] = todoList[i];

		delete[] todoList;
		todoList = newList;
	}
}
void replaceTask(int index, Task task, Task* todoList, int length)
{
	if (0 <= index && index < length)
		todoList[index] = task;
}

void sortByPriority(Task* todoList, int length)
{
	Task* newList = new Task[length];
	
	int counter = 0;

	for (int i = 0; i < length; i++)
		if (todoList[i].priority == VeryImportant)
			newList[counter++] = todoList[i];

	for (int i = 0; i < length; i++)
		if (todoList[i].priority == Important)
			newList[counter++] = todoList[i];
	
	for (int i = 0; i < length; i++)
		if (todoList[i].priority == NotImportant)
			newList[counter++] = todoList[i];

	delete[] todoList;
	todoList = newList;
}
void sortByDeadline(Task* todoList, int length)
{
	if (length > 1)
	{
		int pivotIndex = length / 2;
		Task pivot = todoList[pivotIndex];

		int lenLess = 0;
		int lenMore = 0;

		Task* less = new Task[lenLess];
		Task* more = new Task[lenMore];

		for (int i = 0; i < length; i++)
		{
			if (i != pivotIndex)
			{
				if (dateCmp(todoList[i].deadline, pivot.deadline) == -1)
					addTask(todoList[i], more, lenMore);
				else
					addTask(todoList[i], less, lenLess);
			}
		}

		sortByDeadline(less, lenLess);
		sortByDeadline(more, lenMore);

		for (int i = 0; i < lenLess; i++)
			todoList[i] = less[i];
		todoList[lenLess] = pivot;
		for (int i = 0; i < lenMore; i++)
			todoList[lenLess + 1 + i] = more[i];
	}
}
void sortByCreationDate(Task* todoList, int length)
{
	if (length > 1)
	{
		int pivotIndex = length / 2;
		Task pivot = todoList[pivotIndex];

		int lenLess = 0;
		int lenMore = 0;

		Task* less = new Task[lenLess];
		Task* more = new Task[lenMore];

		for (int i = 0; i < length; i++)
		{
			if (i != pivotIndex)
			{
				if (dateCmp(todoList[i].creationDate, pivot.creationDate) == -1)
					addTask(todoList[i], more, lenMore);
				else
					addTask(todoList[i], less, lenLess);
			}
		}

		sortByDeadline(less, lenLess);
		sortByDeadline(more, lenMore);

		for (int i = 0; i < lenLess; i++)
			todoList[i] = less[i];
		todoList[lenLess] = pivot;
		for (int i = 0; i < lenMore; i++)
			todoList[lenLess + 1 + i] = more[i];
	}
}

