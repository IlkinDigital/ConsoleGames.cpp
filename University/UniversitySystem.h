#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "Exception.h"

class Person
{
public:
	Person(const std::string& name, const std::string& surname, uint16_t age)
		: m_Name(name), m_Surname(surname), m_Age(age) {}
	Person(std::string&& name, std::string&& surname, uint16_t age)
		: m_Name(name), m_Surname(surname), m_Age(age) {}

	std::string GetName() const { return m_Name; }
	std::string GetSurname() const { return m_Surname; }
	uint16_t GetAge() const { return m_Age; }

	void SetAge(uint16_t age) { m_Age = age; }
	void SetName(const std::string& name) { m_Name = name; }
	void SetSurname(const std::string& surname) { m_Surname = surname; }

	bool operator == (const Person& other) const
	{
		return m_Name == other.m_Name && m_Surname == other.m_Surname && m_Age == other.m_Age;
	}

protected:
	std::string m_Name;
	std::string m_Surname;
	uint16_t m_Age;
};

class Student : public Person
{
public:
	Student(const std::string& name, const std::string& surname, uint16_t age, const std::string& major)
		: Person(name, surname, age), m_Major(major) {}

	void AddGrade(int grade);

	float GPA() const; // 1.0 - 12.0

	bool IsScholarshipEligible() const { return GPA() > 8.0f; }

	std::string GetMajor() const { return m_Major; }
	
	void SetMajor(const std::string& major) { m_Major = major; }
	
private:
	std::vector<int> m_Grades;
	std::string m_Major;
};

class Group
{
public:
	Group(const std::string& groupName)
		: m_Name(groupName) {}

	void AddStudent(const Student& student) { m_Students.push_back(student); }

	size_t Size() const { return m_Students.size(); }

	std::string GetName() const { return m_Name; }
	void SetName(const std::string& name) { m_Name = name; }
private:
	std::string m_Name;
	std::vector<Student> m_Students;
};

class Course
{
public:
	Course(std::string&& name, std::string&& description)
		: m_Name(name), m_Description(description) {}

	std::string GetName() const { return m_Name; }
	std::string GetDescription() const { return m_Description; }

	void SetName(const std::string& name) { m_Name = name; }
	void SetDescription(const std::string& description) { m_Description = description; }

	bool operator == (const Course& other)
	{
		return m_Name == other.m_Name && m_Description == other.m_Description;
	}

private:
	std::string m_Name;
	std::string m_Description;
};

class Professor : public Person
{
public:
	Professor(const std::string& name, const std::string& surname, uint16_t age, const Course& course, uint32_t salary)
		: Person(name, surname, age), m_Course(course), m_Salary(salary) {}

	Course GetCourse() const { return m_Course; }
	uint32_t GetSalary() const { return m_Salary; }

	void SetSalary(uint32_t salary) { m_Salary = salary; }
	void SetCourse(const Course& course) { m_Course = course; }

	bool GroupExists(const Group& g) const;

	void AddGroup(const Group& g);
	void RemoveGroup(const Group& g);

private:
	Course m_Course;
	uint32_t m_Salary;
	std::vector<Group> m_Groups;
};

class Department
{
public:
	Department(const std::string& name, const std::vector<Course>& courses, size_t facultyNum)
		: m_Name(name), m_Courses(courses), m_FacultyNumber(facultyNum) {}

	std::string GetName() const { return m_Name; }
	size_t GetFacultyNumber() const { return m_FacultyNumber; }
	
	void AddCourse(const Course& c) { m_Courses.push_back(c); }
	void RemoveCourse(const Course& c) 
	{ 
		using iterator = std::vector<Course>::iterator;

		for (iterator i = m_Courses.begin(); i != m_Courses.end(); i++)
		{
			if (*i == c)
			{
				m_Courses.erase(i);
				std::cout << "Removed " << i->GetName() << " course from " << m_Name << '.' << std::endl;
			}
		}
	}

	bool operator == (const Department& other) const { return m_Name == other.m_Name && 
															  m_FacultyNumber == other.m_FacultyNumber; }
private:
	std::string m_Name;
	std::vector<Course> m_Courses;
	size_t m_FacultyNumber;
};

class University
{
public:
	University(const std::string& name)
		: m_Name(name) {}

	std::string GetName() const { return m_Name; }
	void SetName(const std::string& name) { m_Name = name; }

	bool DepartmentExists(const Department& d);
	bool ProfessorExists(const Professor& p);
	bool StudentExists(const Student& s);

	void AddDepartment(const Department& d) { m_Departments.push_back(d); }
	void AddProfessor(const Professor& p) { m_Professors.push_back(p); }
	void AddStudent(const Student& s) { m_Students.push_back(s); }

	void RemoveDepartment(const Department& d);
	void RemoveProfessor(const Professor& p);
	void RemoveStudent(const Student& s);

	void IncreaseSalary(const Professor& p, uint32_t byHowMuch);
private:
	std::string m_Name;
	std::vector<Department> m_Departments;
	std::vector<Professor> m_Professors;
	std::vector<Student> m_Students;
};

