#include "ProcessInfo.h"

int ProcessInfo::getPID() const
{
	return m_pid;
}

const std::string ProcessInfo::getUser() const
{
	return m_user;
}

const std::string ProcessInfo::getCommand() const
{
	return m_command;
}

bool ProcessInfo::operator==(const ProcessInfo& other) const
{
	return this->getPID() == other.getPID();
	// return this->getPID() == other.getPID() && this->getUser() == other.getUser() && this->getCommand() == other.getCommand();
}

bool ProcessInfo::operator<(const ProcessInfo& other) const
{
	return this->getPID() < other.getPID();
}
