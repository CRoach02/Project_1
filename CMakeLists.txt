cmake_minimum_required(VERSION 3.20)

project(Project_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Project_1
    src/main.cpp
    src/PrintingFun.cpp
    src/small_scripts/waterfall.cpp
)