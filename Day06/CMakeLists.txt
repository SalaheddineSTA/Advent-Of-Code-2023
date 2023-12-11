set(SOURCES
    src/day_06.cpp
    src/main.cpp
)

add_executable(solveDay06 ${SOURCES})

target_include_directories(solveDay06
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/Day06/include
)
