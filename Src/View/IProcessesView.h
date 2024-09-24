#pragma once

#include <memory>

#include "ProcessesController.h"

class IProcessesView
{
public:
	virtual int start(int argc, char* argv[]) = 0;

	virtual ~IProcessesView() = default;
};