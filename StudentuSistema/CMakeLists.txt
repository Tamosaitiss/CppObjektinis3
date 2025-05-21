cmake_minimum_required(VERSION 3.10)
project(ObjektinisProgramavimas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories (common headerai ir testavimo biblioteka)
include_directories(common external/catch2)

# Vektorių versijos programa su tavo Vector klase
add_executable(vector_version
        Vektoriu_versija/vector_versija.cpp
        common/studentai.cpp
        common/Vector.h
        common/Vector.tpp
)

# Testavimo programa su visais testais (Studentas + Vector)
add_executable(tests
        tests/test_studentas.cpp
        tests/test_vector.cpp
        common/studentai.cpp
)

add_executable(Bench_pushback
        tests/bench_pushback.cpp
        common/Vector.tpp
)

add_executable(Bench_reallocate
        tests/bench_reallocate.cpp
        common/Vector.tpp
)

# Tikslinėms programoms nurodome include direktorijas
target_include_directories(vector_version PRIVATE common)
target_include_directories(tests PRIVATE external/catch2 common)

# Papildomi warning / optimizavimo flag'ai (tik GCC/Clang)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(vector_version PRIVATE -O2 -Wall -Wextra -pedantic)
    target_compile_options(tests PRIVATE -O2 -Wall -Wextra -pedantic)
endif()
