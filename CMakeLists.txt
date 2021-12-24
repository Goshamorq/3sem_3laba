cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(last_laba)

enable_language(C)
enable_language(CXX)

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif ()

include_directories(
        ../3sem_laba3_new/src
)

add_library(
        example
        ../last_laba/src/main.cpp ../last_laba/src/vertex.hpp ../last_laba/src/graph.hpp ../last_laba/src/paint.hpp)

set(GOOGLETEST_ROOT ../last_laba/gtest/googletest CACHE STRING "Google Test source root")

include_directories(
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
)

set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
        )

foreach (_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach ()

add_library(googletest ${GOOGLETEST_SOURCES})

add_executable(
        unit_tests
        ../last_laba/test/main.cpp
        ../last_laba/test/tests.cpp ../last_laba/src/graph.hpp ../last_laba/src/vertex.hpp ../last_laba/src/paint.hpp)

add_executable(
        graph
        ../last_laba/src/graph.hpp ../last_laba/src/vertex.hpp ../last_laba/src/main.cpp ../last_laba/src/paint.hpp)

add_dependencies(unit_tests googletest)

target_link_libraries(
        unit_tests
        googletest
        example
        pthread
)

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)
