cmake_minimum_required(VERSION 3.24)
project(CurvesGeometry VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(LOC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(CurvesGeometry main.cpp
        include/curves.h src/curves.cpp)

add_subdirectory(src)

target_include_directories(CurvesGeometry PUBLIC ${CMAKE_SOURCE_DIR})
