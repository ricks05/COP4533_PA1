cmake_minimum_required(VERSION 3.26)
project(COP4533_PA1)

set(CMAKE_CXX_STANDARD 17)

add_executable(app src/Matching.cpp
        src/main.cpp)
add_executable(test test/test.cpp
        src/Matching.cpp)