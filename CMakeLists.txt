cmake_minimum_required(VERSION 3.12)
project(algorithms)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")

find_package(PkgConfig REQUIRED)

pkg_check_modules(SFML REQUIRED sfml-graphics)
link_directories(${SFML_LIBRARY_DIRS})
include_directories(${SFML_INCLUDE_DIRS})

include_directories(include)

add_subdirectory(external)
add_subdirectory(src)

