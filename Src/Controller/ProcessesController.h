#pragma once
#include <memory>
#include <vector>
#include <functional>

#include "IProcessesModel.h"

class ProcessInfo;

class ProcessesController
{
public:
	ProcessesController(std::unique_ptr<IProcessesModel> model)
		: m_model(std::move(model))
	{
	}
	void startGetProcessesInfoThread(const std::function<void(AddRemoveProcsStruct, int)> cb);
	int killProcess(int pid);
	void setFilter(const std::string filter);

private:
	std::unique_ptr<IProcessesModel> m_model;
};