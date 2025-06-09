cmake_minimum_required(VERSION 3.29)
project(spd3)

set(CMAKE_CXX_STANDARD 20)

add_executable(spd3 main.cpp
        Problem.cpp
        Problem.h
        Solution.cpp
        Solution.h
        algorithms.cpp
        algorithms.h
        Task.cpp
        Task.h
        utils.cpp
        utils.h)
