# Create a library from the source files
add_library(processes_filter ProcessesFilter.h CommandProcessesFilter.cpp)

# Include the current directory for the header files
target_include_directories(processes_filter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(processes_filter process_info)