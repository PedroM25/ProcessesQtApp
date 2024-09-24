# Create a library from the source files
add_library(qt_processes_view QtCustomWindow.cpp QtProcessesWidget.cpp QtProcessesView.cpp)

# Include the current directory for the header files
target_include_directories(qt_processes_view PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(qt_processes_view PUBLIC view Qt5::Widgets)
