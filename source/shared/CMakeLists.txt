add_library(interpreter interpreter.h
                        common-interpreters.h
                        common-interpreters.cpp)
target_link_libraries(interpreter siesta-parser Qt${QT_VERSION_MAJOR}::Core)
