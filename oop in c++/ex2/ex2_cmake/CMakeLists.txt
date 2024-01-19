cmake_minimum_required(VERSION 3.10)

#nazwa projektu
project(ex2_cmake)

#flagi kompilatora
set(CMAKE_CXX_STANDARD 23)

#dodanie plików źródłowych do projektu
add_executable(program main.cpp message.cpp)