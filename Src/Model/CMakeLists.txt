# Create a library from the source files
add_library(model IProcessesModel.h)

# Include the current directory for the header files
target_include_directories(model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(model add_remove_procs_struct)

add_subdirectory(ModelFactory)
add_subdirectory(ProcessesInfo)
add_subdirectory(Unix)
add_subdirectory(ProcessesFilter)
add_subdirectory(ProcessesDiff)
add_subdirectory(AddRemoveProcsStruct)
