#pragma once

#include <string>

namespace Exception
{
	class Base
	{
	public:
		Base()
			: m_Message("Unknown exception."), m_ErrCode(0) {}
		Base(std::string&& message)
			: m_Message(message), m_ErrCode(0) {}
		Base(std::string&& message, int code)
			: m_Message(message), m_ErrCode(code) {}

		virtual std::string Message() const { return m_Message; }
		virtual int ErrorCode() const { return m_ErrCode; }
	protected:
		std::string m_Message;
		int m_ErrCode;
	}; 

	class InvalidGrade : public Base
	{
	public:
		InvalidGrade() = default;

		std::string Message() const override { return "Specified grade is invalid or out of range."; }
		int ErrorCode() const override { return 400; }
	};

	class InvalidSalary : public Base
	{
	public:
		InvalidSalary() = default;

		std::string Message() const override { return "Specified salary is invalid or out of range."; }
		int ErrorCode() const override { return 400; }
	};

	class InvalidGroup : public Base
	{
	public:
		InvalidGroup() = default;

		std::string Message() const override { return "Specified group doesn't exist."; }
		int ErrorCode() const override { return 404; }
	};	
	
	class InvalidStudent : public Base
	{
	public:
		InvalidStudent() = default;

		std::string Message() const override { return "Specified student doesn't exist."; }
		int ErrorCode() const override { return 404; }
	};	
	
	class InvalidProfessor : public Base
	{
	public:
		InvalidProfessor() = default;

		std::string Message() const override { return "Specified professor doesn't exist."; }
		int ErrorCode() const override { return 404; }
	};
	
	class InvalidDepartment : public Base
	{
	public:
		InvalidDepartment() = default;

		std::string Message() const override { return "Specified department doesn't exist."; }
		int ErrorCode() const override { return 404; }
	};



	class GroupDuplication : public Base
	{
	public:
		GroupDuplication() = default;

		std::string Message() const override { return "Group buffer can't have groups with the same name."; }
		int ErrorCode() const override { return 401; }
	};	
	

}
