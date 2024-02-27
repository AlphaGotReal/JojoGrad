cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(JojoGrad VERSION 1.0)

include_directories(include)
add_executable(run src/main.cpp)
