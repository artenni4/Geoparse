cmake_minimum_required(VERSION 3.10)

project(Geoparse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/Simplexer)
add_subdirectory(src)
add_subdirectory(test)
