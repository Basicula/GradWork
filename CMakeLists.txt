cmake_minimum_required(VERSION 3.8)

project(engine)

set(CMAKE_CXX_STANDARD 11)

# for python integration
add_subdirectory(pybind11)

# aditional packages
add_subdirectory(cmake)

# to future testing libs
enable_testing()

# main lib
add_subdirectory(engine)
