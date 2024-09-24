# Create a library from the source files
add_library(controller ProcessesController.cpp)

# Include the current directory for the header files
target_include_directories(controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(controller process_info model)