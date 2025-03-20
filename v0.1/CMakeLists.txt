cmake_minimum_required(VERSION 3.10)
project(ObjektinisProgramavimas)

set(CMAKE_CXX_STANDARD 17)

# Add vector version
add_executable(vector_version
        "Vektoriu_versija/vector_versija.cpp"
        "Vektoriu_versija/studentai.cpp"
)

# Add list version
add_executable(list_version
        "List_versija/list_versija.cpp"
        "List_versija/studentai.cpp"
)

# Add deque version
add_executable(deque_version
        "Deque_versija/deque_versija.cpp"
        "Deque_versija/studentai.cpp"
)

# Include headers
include_directories("Vektoriu_versija" "List_versija" "Deque_versija")

# Compiler flags for warnings & optimizations
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(vector_version PRIVATE -O2 -Wall -Wextra -pedantic)
    target_compile_options(list_version PRIVATE -O2 -Wall -Wextra -pedantic)
    target_compile_options(deque_version PRIVATE -O2 -Wall -Wextra -pedantic)
endif()