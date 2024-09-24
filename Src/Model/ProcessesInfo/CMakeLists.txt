# Create a library from the source files
add_library(process_info ProcessInfo.cpp)

# Include the current directory for the header files
target_include_directories(process_info PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})