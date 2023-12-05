set(SOURCES
    src/day_03.cpp
    src/main.cpp
)

add_executable(solveDay03 ${SOURCES})

target_include_directories(solveDay03
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/Day03/include
)
