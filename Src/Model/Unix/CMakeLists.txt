# Create a library from the source files
add_library(unix_model UnixProcessesModel.cpp)

# Include the current directory for the header files
target_include_directories(unix_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(unix_model 
    process_info
    model
    processes_filter
    processes_diff
    Qt5::Widgets
)