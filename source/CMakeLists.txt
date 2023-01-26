add_subdirectory(configure)
add_subdirectory(shared)
add_subdirectory(siesta-graph)
add_subdirectory(siesta-manager)
add_subdirectory(siesta-parser)

add_executable(main main.cpp)
target_link_libraries(main configure 
                           siesta-graph 
                           siesta-manager 
                           siesta-parser 
                           Qt${QT_VERSION_MAJOR}::Widgets 
                           Qt${QT_VERSION_MAJOR}::Core)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "..." FORCE)
endif()

install(FILES "../examples/output/siesta.out" DESTINATION ${EXECUTION_DIR})
install(FILES "../examples/input/source.fdf" 
              "../examples/input/H.psf"
              "../examples/input/Si.psf"
        DESTINATION ${EXECUTION_DIR})
install(TARGETS main DESTINATION .)
