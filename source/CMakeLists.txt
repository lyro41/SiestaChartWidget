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
                           Qt${QT_VERSION_MAJOR}::Core
                           ${Qt${QT_VERSION_MAJOR}Widgets_LIBRARIES}
                           ${Qt${QT_VERSION_MAJOR}Core_LIBRARIES}
                           ${Qt${QT_VERSION_MAJOR}Gui_LIBRARIES}
                           ${Qt${QT_VERSION_MAJOR}Charts_LIBRARIES})

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "..." FORCE)
endif()

install(CODE "set(EXECUTION_DIR ${CMAKE_INSTALL_PREFIX})")
install(CODE "file(MAKE_DIRECTORY ${EXECUTION_DIR})")
install(CODE "file(MAKE_DIRECTORY ${CHARTS_OUTPUT})")
install(FILES "../examples/output/siesta.out" DESTINATION .)
install(FILES "../examples/input/source.fdf" 
              "../examples/input/H.psf"
              "../examples/input/Si.psf"
        DESTINATION .)
if (WIN32)
  install(FILES $<TARGET_RUNTIME_DLLS:main> DESTINATION .)
  install(FILES "$<TARGET_FILE:Qt5::QWindowsIntegrationPlugin>" DESTINATION ./platforms)
  install(DIRECTORY ${PROJECT_BINARY_DIR}/$<CONFIG>/ DESTINATION . FILES_MATCHING PATTERN "*.dll")
else (WIN32)
  install(DIRECTORY ${PROJECT_BINARY_DIR}/$<CONFIG>/ DESTINATION . FILES_MATCHING PATTERN "*.so")
endif (WIN32)
install(IMPORTED_RUNTIME_ARTIFACTS Qt${QT_VERSION_MAJOR}::Charts 
                                   Qt${QT_VERSION_MAJOR}::Core
                                   Qt${QT_VERSION_MAJOR}::Widgets
                                   Qt${QT_VERSION_MAJOR}::Gui
                                   main
        DESTINATION .)
install(TARGETS main DESTINATION .)
