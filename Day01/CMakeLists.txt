set(SOURCES
    src/day_01.cpp
    src/main.cpp
)

add_executable(solveDay01 ${SOURCES})

target_include_directories(solveDay01
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/Day01/include
)
