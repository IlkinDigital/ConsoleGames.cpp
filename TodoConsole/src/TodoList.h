#pragma once

#include <iostream>
#include <time.h>
#include <ctime>

enum Priority
{
	NotImportant, Important, VeryImportant
};

struct Date
{
	int hour;
	int minute;
	int second;
	int year;
	int month;
	int day;
};

struct Task
{
	char* title;
	char* description;
	Priority priority;
	Date creationDate;
	Date deadline;
};

// Helpers
bool isSubstring(char* sub, int lenSub, char* main, int lenMain);
bool dateCmp(Date date1, Date date2);

Date createDate(int day, int month, int year, int sec = -1, int minute = -1, int hour = -1);
Date currentDate();

Task createTask(char* title, char* description, Date deadline, Priority priority = NotImportant);
void addTask(Task newTask, Task* todoList, int& length);
void removeTask(int index, Task* todoList, int& length);
void replaceTask(int index, Task task, Task* todoList, int length);

// Sorts
void sortByPriority(Task* todoList, int length);
void sortByDeadline(Task* todoList, int length);
void sortByCreationDate(Task* todoList, int length);

// Search


void drawTodoList(Task* todoList);



