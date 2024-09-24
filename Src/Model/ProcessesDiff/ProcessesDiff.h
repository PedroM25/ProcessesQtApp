#pragma once

#include <string>
#include <set>
#include <vector>

#include "AddRemoveProcsStruct.h"

class ProcessInfo;

class ProcessesDiff
{
public:
	AddRemoveProcsStruct calculateDiff(const std::set<ProcessInfo>& processesUpdated);

private:
	std::set<ProcessInfo> previousProcessesSet;
};
