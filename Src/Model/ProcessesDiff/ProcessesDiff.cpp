#include "ProcessesDiff.h"

#include <algorithm>

#include "ProcessInfo.h"

AddRemoveProcsStruct ProcessesDiff::calculateDiff(const std::set<ProcessInfo>& detectedProcesses)
{
	std::set<ProcessInfo> toAdd{};
	std::set<ProcessInfo> toRemove{};

	// first, check new ones to add
	std::set_difference(
		previousProcessesSet.begin(),
		previousProcessesSet.end(),
		detectedProcesses.begin(),
		detectedProcesses.end(),
		std::inserter(toRemove, toRemove.begin()));

	// second, which ones should be removed?
	std::set_difference(
		detectedProcesses.begin(),
		detectedProcesses.end(),
		previousProcessesSet.begin(),
		previousProcessesSet.end(),
		std::inserter(toAdd, toAdd.begin()));

	// TO FINISH: Add elements from toAdd to previousProcessesSet
	previousProcessesSet.insert(toAdd.begin(), toAdd.end());

	// TO FINISH: Remove elements present in toRemove that are also present in previousProcessesSet
	for (const ProcessInfo& elem : toRemove)
	{
		previousProcessesSet.erase(elem);
	}

	return AddRemoveProcsStruct{toAdd, toRemove};
}
