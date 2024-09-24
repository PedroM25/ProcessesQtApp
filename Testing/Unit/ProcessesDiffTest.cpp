#include <memory>
#include <iostream>

#include <gtest/gtest.h>

#include "ProcessesDiff.h"
#include "ProcessInfo.h"

using namespace testing;

namespace{
	const std::string USER = "User";
	const std::string COMMAND = "Command";
}

class ProcessesDiffTest : public Test
{
protected:
	void SetUp() override {}

	void TearDown() override {}

	ProcessesDiff procDiff{};
};

TEST_F(ProcessesDiffTest, ReturnPairIsCorrect)
{	
	// first diff calculation
	const std::set<ProcessInfo> DETECTED_PROCESSES_1{
		{1, USER, COMMAND},
		{2, USER, COMMAND},
		{3, USER, COMMAND},
		{10, USER, COMMAND},
		{15, USER, COMMAND},
	};
	const std::set<ProcessInfo> EXPECTED_TO_ADD_SET_1{
		{1, USER, COMMAND},
		{2, USER, COMMAND},
		{3, USER, COMMAND},
		{10, USER, COMMAND},
		{15, USER, COMMAND},
	};
	const std::set<ProcessInfo> EXPECTED_TO_REMOVE_SET_1{};

	// second diff calculation
	const std::set<ProcessInfo> DETECTED_PROCESSES_2{
		{1, USER, COMMAND},
		{2, USER, COMMAND},
		{10, USER, COMMAND},
		{18, USER, COMMAND},
	};
	const std::set<ProcessInfo> EXPECTED_TO_ADD_SET_2{
		{18, USER, COMMAND},
	};
	const std::set<ProcessInfo> EXPECTED_TO_REMOVE_SET_2{
		{3, USER, COMMAND},
		{15, USER, COMMAND},
	};

	auto ret = procDiff.calculateDiff(DETECTED_PROCESSES_1);
	ASSERT_EQ(ret.getToAdd(), EXPECTED_TO_ADD_SET_1) << "Return from .calculateDiff toAdd not equal to EXPECTED_RES_1 toAdd";
	ASSERT_EQ(ret.getToRemove(), EXPECTED_TO_REMOVE_SET_1) << "Return from .calculateDiff toRemove not equal to EXPECTED_RES_1 toRemove";

	ret = procDiff.calculateDiff(DETECTED_PROCESSES_2);
	ASSERT_EQ(ret.getToAdd(), EXPECTED_TO_ADD_SET_2) << "Return from .calculateDiff toAdd not equal to EXPECTED_RES_2 toAdd";
	ASSERT_EQ(ret.getToRemove(), EXPECTED_TO_REMOVE_SET_2) << "Return from .calculateDiff toRemove not equal to EXPECTED_RES_2 toRemove";

	/*

	ASSERT_EQ(ret.size(), EXPECTED_RES_1.size()) << "std::set ret and EXPECTED_RES_1 are of unequal length";

	for (int i = 0; i < EXPECTED_RES_1.size(); ++i)
	{
		EXPECT_EQ(exampleReturn[i], ret[i]) << "Vectors exampleReturn and ret differ at index " << i;
	}
	*/
}
