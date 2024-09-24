#include "ProcessesController.h"

void ProcessesController::startGetProcessesInfoThread(const std::function<void(AddRemoveProcsStruct, int)> cb)
{
	m_model->startGetProcessesInfoThread(cb);
}

int ProcessesController::killProcess(int pid)
{
	return m_model->killProcess(pid);
}

void ProcessesController::setFilter(const std::string filter)
{
	m_model->setFilter(filter);
}