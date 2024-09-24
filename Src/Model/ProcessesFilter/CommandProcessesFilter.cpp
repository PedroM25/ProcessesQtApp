#include "CommandProcessesFilter.h"
#include "ProcessInfo.h"

std::set<ProcessInfo> CommandProcessesFilter::performFiltering(const std::set<ProcessInfo>& processes) const
{
	if (m_currFilter.empty())
	{
		return processes;
	}

	std::set<ProcessInfo> filtered{};
	for (auto& procInf : processes)
	{
		if (procInf.getCommand().find(m_currFilter) != procInf.getCommand().npos)
		{
			filtered.insert(procInf);
		}
	}
	return filtered;
}
