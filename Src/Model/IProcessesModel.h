#pragma once
#include <string>
#include <functional>

#include "AddRemoveProcsStruct.h"

class ProcessInfo; 

class IProcessesModel
{
public:
	virtual void startGetProcessesInfoThread(const std::function<void(AddRemoveProcsStruct, int)> cb) = 0;
	virtual int killProcess(pid_t pid) const = 0;
	virtual void setFilter(const std::string filter) = 0; // PEDRO: did this because this is an interface... if it was an abstract class, ProcessesFilter could be attribute

	virtual ~IProcessesModel() = default;
};