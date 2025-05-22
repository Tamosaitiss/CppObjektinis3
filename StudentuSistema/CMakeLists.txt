cmake_minimum_required(VERSION 3.10)
project(ObjektinisProgramavimas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 💡 STATIC FLAGS – svarbu, kad veiktų be DLL
set(CMAKE_CXX_FLAGS_DEBUG "-static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS_RELEASE "-static -static-libgcc -static-libstdc++")

# Include directories
include_directories(common external/catch2)

# Vektorių versijos programa (su tavo Vector klase)
add_executable(vector_version
        Vektoriu_versija/vector_versija.cpp
        common/studentai.cpp
        common/Vector.h
        common/Vector.tpp
)

# Testai (studentas ir vector)
add_executable(tests
        tests/test_studentas.cpp
        tests/test_vector.cpp
        common/studentai.cpp
)

# Benchmark'ai
add_executable(Bench_pushback
        tests/bench_pushback.cpp
        common/Vector.tpp
)

add_executable(Bench_reallocate
        tests/bench_reallocate.cpp
        common/Vector.tpp
)

# Include paths
target_include_directories(vector_version PRIVATE common)
target_include_directories(tests PRIVATE external/catch2 common)

# Compiler warnings (GCC / Clang only)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(vector_version PRIVATE -O2 -Wall -Wextra -pedantic)
    target_compile_options(tests PRIVATE -O2 -Wall -Wextra -pedantic)
endif()