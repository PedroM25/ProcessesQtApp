#include <memory>
#include <iostream>

#include <gtest/gtest.h>

#include "ProcessesFilter.h"
#include "CommandProcessesFilter.h"
#include "ProcessInfo.h"

using namespace testing;

namespace{
	const std::string USER = "User";
	const std::string COMMAND = "Command";
}

class ProcessesFilterTest : public Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

	std::unique_ptr<ProcessesFilter> procFilter = std::make_unique<CommandProcessesFilter>();
};

TEST_F(ProcessesFilterTest, FilterIsCorrect)
{	
	const std::set<ProcessInfo> PROCESSES_1{
		{1, USER, "test1"},
		{2, USER, "test2"},
		{3, USER, "test333"},
		{4, USER, "Test44"},
		{5, USER, "NewTest5"},
		{6, USER, "Newtest66"},
	};

	const std::set<ProcessInfo> EXPECTED_RET{
		{1, USER, "test1"},
		{2, USER, "test2"},
		{3, USER, "test333"},
		{6, USER, "Newtest66"},
	};
	procFilter->setFilter("test");
	auto ret = procFilter->performFiltering(PROCESSES_1);

	ASSERT_EQ(ret, EXPECTED_RET) << "Return from performFiltering different from PROCESSES_1";
}
