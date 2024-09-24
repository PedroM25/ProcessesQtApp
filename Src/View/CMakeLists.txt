# Create a library from the source files
add_library(view IProcessesView.h)

# Include the current directory for the header files
target_include_directories(view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(Qt)

target_link_libraries(view controller)