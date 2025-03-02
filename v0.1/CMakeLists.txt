cmake_minimum_required(VERSION 3.30)
project(ObjektinisProgramavimas)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ObjektinisProgramavimas
        vektorine_versija.cpp
        studentai.cpp
        studentai.h)
