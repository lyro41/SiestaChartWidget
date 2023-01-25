add_subdirectory(configure)
add_subdirectory(shared)
add_subdirectory(siesta-graph)
add_subdirectory(siesta-manager)
add_subdirectory(siesta-parser)

add_executable(main main.cpp)
target_link_libraries(main configure siesta-graph siesta-manager siesta-parser Qt5::Widgets Qt5::Core)

install(FILES "examples/output/siesta.out" DESTINATION EXECUTION_DIR)
install(FILES "examples/output/source.fdf" 
              "examples/input/H.psf"
              "examples/input/H.psf"
        DESTINATION EXECUTION_DIR)
install(TARGETS main DESTINATION .)
