set(SOURCES
    src/day_04.cpp
    src/main.cpp
)

add_executable(solveDay04 ${SOURCES})

target_include_directories(solveDay04
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/Day04/include
)
