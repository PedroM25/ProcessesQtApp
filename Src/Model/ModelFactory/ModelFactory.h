#pragma once

#include <memory>

class IProcessesModel;

class ModelFactory
{
public:
	std::unique_ptr<IProcessesModel> getPlatformDependentModel() const;
};