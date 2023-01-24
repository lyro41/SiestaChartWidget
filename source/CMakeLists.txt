add_subdirectory(configure)
add_subdirectory(shared)
add_subdirectory(siesta-graph)
add_subdirectory(siesta-manager)
add_subdirectory(siesta-parser)

add_executable(main main.cpp)
target_link_libraries(main configure siesta-graph siesta-manager siesta-parser Qt5::Widgets Qt5::Core)

install(TARGETS main DESTINATION .)
