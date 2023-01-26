include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(siesta-graph siesta-chart-widget.h 
                         siesta-chart-widget.cpp
                         siesta-chart.h
                         siesta-chart.cpp
                         siesta-graph.h
                         siesta-graph.cpp
                         qparser.h
                         qparser.cpp)
target_link_libraries(siesta-graph siesta-parser 
                                   interpreter 
                                   Qt${QT_VERSION_MAJOR}::Widgets 
                                   Qt${QT_VERSION_MAJOR}::Core 
                                   Qt${QT_VERSION_MAJOR}::Charts)
