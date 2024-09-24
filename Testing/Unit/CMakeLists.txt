enable_testing()

add_executable(
    unit_tests
    ProcessesControllerTest.cpp
    ProcessesDiffTest.cpp
    ProcessesFilterTest.cpp
)

target_link_libraries(
    unit_tests
    GTest::gtest_main
    GTest::gmock_main
    controller
    processes_diff
    processes_filter
    mocks
)

include(GoogleTest)
gtest_discover_tests(unit_tests)