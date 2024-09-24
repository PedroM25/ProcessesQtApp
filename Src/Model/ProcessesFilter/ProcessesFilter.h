#pragma once

#include <set>
#include <string>

class ProcessInfo;

/*
 * Abstract class
 */
class ProcessesFilter
{
public:
	virtual std::set<ProcessInfo> performFiltering(const std::set<ProcessInfo>& processes) const = 0;
	void setFilter(std::string filter)
	{
		m_currFilter = filter;
	};

	virtual ~ProcessesFilter() = default;
	
protected:
	ProcessesFilter(std::string filter = {})
		: m_currFilter(filter){};

	std::string m_currFilter;
};
