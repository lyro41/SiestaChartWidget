# set minimum version of cmake required for the project
cmake_minimum_required(VERSION 3.16)

# enable required languages
enable_language(C)
enable_language(CXX)

# set project name, version and required languages
project(coursework
        VERSION 3.16.3
        LANGUAGES C CXX)

# specify the C standard
set(CMAKE_C_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED true)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

# link Qt packages
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
find_package(Qt5Charts)

find_package(Doxygen)
if(DOXYGEN_FOUND)
  add_custom_target(docs ${DOXYGEN_EXECUTABLE} docs.doxyfile
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM
  SOURCES ${PRJ_DOXY}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

# include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(source)

# create paths to data files
set(EXECUTION_DIR "${CMAKE_CURRENT_BINARY_DIR}/execution")
set(SIESTA_CONFIG "${EXECUTION_DIR}/siesta.cfg")
set(CHARTS_OUTPUT "${EXECUTION_DIR}/charts")

# set up execution data directory
file(MAKE_DIRECTORY ${EXECUTION_DIR})
file(MAKE_DIRECTORY ${CHARTS_OUTPUT})

# add configuration file
configure_file(config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/config.h @ONLY)
configure_file(config.h.in config.h @ONLY)

add_subdirectory(source)
