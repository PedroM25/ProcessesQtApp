#pragma once

#include "ProcessesFilter.h"

class CommandProcessesFilter : public ProcessesFilter
{
public:
	std::set<ProcessInfo> performFiltering(const std::set<ProcessInfo>& processes) const override;
	
	CommandProcessesFilter(std::string filter = {})
		: ProcessesFilter(filter){};
};
