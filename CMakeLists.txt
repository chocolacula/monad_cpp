project(monad_cpp)
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD  17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output)

add_executable(monad main.cpp)
