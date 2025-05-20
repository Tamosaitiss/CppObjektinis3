cmake_minimum_required(VERSION 3.10)
project(ObjektinisProgramavimas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(common external/catch2)

# Vektorių versijos programa
add_executable(vector_version
        Vektoriu_versija/vector_versija.cpp
        common/studentai.cpp
)

# Testų programa su Catch2
add_executable(tests
        tests/test_studentas.cpp
        common/studentai.cpp
)

# Bendros include direktorijos (ir Catch2, ir tavo headeriai)
target_include_directories(vector_version PRIVATE common)
target_include_directories(tests PRIVATE external/catch2 common)

# Papildomi warning / optimizavimo flag'ai (tik GCC/Clang)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(vector_version PRIVATE -O2 -Wall -Wextra -pedantic)
    target_compile_options(tests PRIVATE -O2 -Wall -Wextra -pedantic)
endif()
