cmake_minimum_required(VERSION 3.30)
project(Gleichungssysteme)

set(CMAKE_CXX_STANDARD 20)

add_executable(Gleichungssysteme main.cpp
        matrix.hpp
        verfahrenLogik.cpp
        importLogik.cpp
        test.hpp
        test.cpp)
