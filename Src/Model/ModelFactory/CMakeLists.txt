# Create a library from the source files
add_library(model_factory ModelFactory.cpp)

# Include the current directory for the header files
target_include_directories(model_factory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(model_factory unix_model)