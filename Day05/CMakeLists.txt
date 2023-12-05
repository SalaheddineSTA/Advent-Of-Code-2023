set(SOURCES
    src/day_05.cpp
    src/main.cpp
)

add_executable(solveDay05 ${SOURCES})

target_include_directories(solveDay05
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/Day05/include
)
