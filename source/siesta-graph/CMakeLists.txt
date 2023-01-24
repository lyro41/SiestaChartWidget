include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(siesta-graph siesta-chart-widget.h 
                         siesta-chart-widget.cpp
                         siesta-chart.h
                         siesta-chart.cpp
                         siesta-graph.h
                         siesta-graph.cpp
                         qparser.h
                         qparser.cpp)
target_link_libraries(siesta-graph siesta-parser interpreter Qt5::Widgets Qt5::Core Qt5::Charts)
