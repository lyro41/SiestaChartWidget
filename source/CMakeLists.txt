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

if (BUILD_SHARED_LIBS)
  foreach(DEP ${DEPS})
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                       COMMAND ${CMAKE_COMMAND} -E copy
                       $<TARGET_FILE:${DEP}>
                       $<TARGET_FILE_DIR:${PROJECT_NAME}>)
  endforeach()
endif()

install(CODE "set(EXECUTION_DIR ${CMAKE_INSTALL_PREFIX})")
install(CODE "file(MAKE_DIRECTORY ${EXECUTION_DIR})")
install(CODE "file(MAKE_DIRECTORY ${CHARTS_OUTPUT})")
install(FILES "../examples/output/siesta.out" DESTINATION .)
install(FILES "../examples/input/source.fdf" 
              "../examples/input/H.psf"
              "../examples/input/Si.psf"
        DESTINATION .)
install(IMPORTED_RUNTIME_ARTIFACTS Qt${QT_VERSION_MAJOR}::Charts 
                                   Qt${QT_VERSION_MAJOR}::Core
                                   Qt${QT_VERSION_MAJOR}::Widgets
                                   DESTINATION .)
install(TARGETS main DESTINATION .)
