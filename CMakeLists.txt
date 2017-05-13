cmake_minimum_required(VERSION 3.3)
project(C_audio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(C_audio ${SOURCE_FILES})