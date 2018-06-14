cmake_minimum_required(VERSION 3.9)
project(cppjit)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppjit src/memory_pages.cpp src/memory_pages.h src/main.cpp)