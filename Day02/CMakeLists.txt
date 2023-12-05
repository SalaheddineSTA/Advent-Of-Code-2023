set(SOURCES
    src/day_02.cpp
    src/main.cpp
)

add_executable(solveDay02 ${SOURCES})

target_include_directories(solveDay02
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/Day02/include
)
