#pragma once

#include "IProcessesView.h"

class QtProcessesView : public IProcessesView
{
public:
	int start(int argc, char* argv[]) override;

	QtProcessesView(std::unique_ptr<ProcessesController> processesController)
		: m_processesController(std::move(processesController)){};

private:
	std::unique_ptr<ProcessesController> m_processesController;
};