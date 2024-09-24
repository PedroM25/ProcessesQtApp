#include "ModelFactory.h"

#include "UnixProcessesModel.h"

std::unique_ptr<IProcessesModel> ModelFactory::getPlatformDependentModel() const
{
#ifdef __unix__
	return std::make_unique<UnixProcessesModel>();
#endif

#ifdef _WIN32
	return std::make_shared<WindowsProcessesModel>(); // Not supported
#endif
}