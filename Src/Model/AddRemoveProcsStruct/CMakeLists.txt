# Create a library from the source files
add_library(add_remove_procs_struct AddRemoveProcsStruct.h)

# Include the current directory for the header files
target_include_directories(add_remove_procs_struct PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
