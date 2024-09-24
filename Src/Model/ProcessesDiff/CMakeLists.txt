# Create a library from the source files
add_library(processes_diff ProcessesDiff.cpp)

# Include the current directory for the header files
target_include_directories(processes_diff PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(processes_diff 
    process_info
    add_remove_procs_struct
)