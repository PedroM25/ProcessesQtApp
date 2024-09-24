#pragma once
#include <string>

class ProcessInfo
{
public:
	int getPID() const;
	const std::string getUser() const;
	const std::string getCommand() const;
	ProcessInfo(int pid, std::string user, std::string command)
		: m_pid(pid)
		, m_user(user)
		, m_command(command)
	{
	}
	bool operator==(const ProcessInfo& other) const;
	bool operator<(const ProcessInfo& other) const;

private:
	int m_pid;
	std::string m_user;
	std::string m_command;
};
