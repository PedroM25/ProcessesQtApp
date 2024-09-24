#include <memory>

#include <gtest/gtest.h>

#include "ProcessesController.h"
#include "ProcessesModelMock.cpp"

using namespace testing;

class ProcessesControllerTest : public Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

	ProcessesModelMock processesModelMock;
};

TEST_F(ProcessesControllerTest, KillProcessCalled)
{
	const int EXAMPLE_RETURN{25};
	const int EXAMPLE_PID{1001};

	auto mock = std::make_unique<ProcessesModelMock>();
	EXPECT_CALL(*mock, killProcess(_)).Times(1).WillOnce(Return(EXAMPLE_RETURN));
	ProcessesController controller(std::move(mock));
	auto ret = controller.killProcess(EXAMPLE_PID);

	ASSERT_EQ(ret, EXAMPLE_RETURN) << "Return from controller and model differ";
}
