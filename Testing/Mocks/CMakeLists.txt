# Create a library from the source files
add_library(mocks ProcessesModelMock.cpp)

# Include the current directory for the header files
target_include_directories(mocks PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(mocks 
    model
    process_info
    GTest::gmock_main
)
