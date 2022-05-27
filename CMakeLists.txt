cmake_minimum_required(VERSION 3.20)
project(Matrix_class)

set(CMAKE_CXX_STANDARD 14)

add_executable(Matrix_class main.cpp Matrix.cpp Matrix.h Hamming.cpp Hamming.h)
