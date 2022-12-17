#include "UniversitySystem.h"

void Student::AddGrade(int grade)
{
	if (grade < 1 || grade > 12)
		throw Exception::InvalidGrade();

	m_Grades.push_back(grade);
}

float Student::GPA() const
{
	float gpa = 0.0f;

	for (auto& item : m_Grades)
	{
		gpa += item;
	}

	gpa /= m_Grades.size();

	return gpa;
}

bool Professor::GroupExists(const Group& g) const
{
	for (const auto& item : m_Groups)
		if (item.GetName() == g.GetName())
			return true;

	return false;
}

void Professor::AddGroup(const Group& g)
{
	if (GroupExists(g))
		throw Exception::GroupDuplication();

	m_Groups.push_back(g);
}

void Professor::RemoveGroup(const Group& g)
{
	if (!GroupExists(g))
		throw Exception::InvalidGroup();

	for (int i = 0; i < m_Groups.size(); i++)
		if (m_Groups[i].GetName() == g.GetName())
			m_Groups.erase(m_Groups.begin() + i);
}

bool University::DepartmentExists(const Department& d)
{
	for (auto& item : m_Departments)
		if (item == d)
			return true;

	return false;
}
bool University::ProfessorExists(const Professor& p)
{
	for (auto& item : m_Professors)
		if (item == p)
			return true;

	return false;
}
bool University::StudentExists(const Student& s)
{
	for (auto& item : m_Students)
		if (item == s)
			return true;

	return false;
}

void University::RemoveDepartment(const Department& d)
{
	if (!DepartmentExists(d))
		throw Exception::InvalidDepartment();
	
	for (int i = 0; i < m_Departments.size(); i++)
		if (m_Departments[i] == d)
			m_Departments.erase(m_Departments.begin() + i);
}

void University::RemoveProfessor(const Professor& p)
{
	if (!ProfessorExists(p))
		throw Exception::InvalidProfessor();

	for (int i = 0; i < m_Professors.size(); i++)
		if (m_Professors[i] == p)
			m_Professors.erase(m_Professors.begin() + i);
}

void University::RemoveStudent(const Student& s)
{
	if (!StudentExists(s))
		throw Exception::InvalidStudent();

	for (int i = 0; i < m_Students.size(); i++)
		if (m_Students[i] == s)
			m_Students.erase(m_Students.begin() + i);
}

void University::IncreaseSalary(const Professor& p, uint32_t byHowMuch)
{
	for (auto& item : m_Professors)
	{
		if (item == p)
		{
			item.SetSalary(item.GetSalary() + byHowMuch);
			return;
		}
	}

	throw Exception::InvalidProfessor();
}
