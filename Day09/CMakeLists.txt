set(SOURCES
    src/day_09.cpp
    src/main.cpp
)

add_executable(solveDay09 ${SOURCES})

target_include_directories(solveDay09
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/Day09/include
)
