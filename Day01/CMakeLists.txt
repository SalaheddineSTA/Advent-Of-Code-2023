cmake_minimum_required(VERSION 3.5)

project (AdventCode)

set(SOURCES
    src/day_01.cpp
    src/main.cpp
)

add_executable(AdventCode ${SOURCES})

target_include_directories(AdventCode
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)
