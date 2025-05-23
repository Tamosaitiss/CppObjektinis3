cmake_minimum_required(VERSION 3.10)
project(ObjektinisProgramavimas)

set(CMAKE_CXX_STANDARD 17)

# Include headers from common
include_directories(common)

# Add vector version
add_executable(vector_version
        Vektoriu_versija/vector_versija.cpp
        common/studentai.cpp
)

# Compiler flags for warnings & optimizations
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(vector_version PRIVATE -O2 -Wall -Wextra -pedantic)
endif()
