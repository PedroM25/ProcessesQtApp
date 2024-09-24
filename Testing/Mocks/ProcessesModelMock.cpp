#include <gmock/gmock.h> // Brings in gMock.

#include "IProcessesModel.h"
#include "ProcessInfo.h"
#include "AddRemoveProcsStruct.h"

class ProcessesModelMock : public IProcessesModel
{
public:
	MOCK_METHOD(void, startGetProcessesInfoThread, (const std::function<void(AddRemoveProcsStruct, int)>), (override));
	MOCK_METHOD(int, killProcess, (pid_t pid), (const, override));
	MOCK_METHOD(void, setFilter, (const std::string filter), (override));
};