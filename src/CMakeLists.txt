﻿add_executable(${PROJECT_NAME}
        main.cpp
        Game.cpp
        Game.h
        systems/System.h
        systems/SystemManager.h
        World.h
        World.cpp
        algorithms/IProceduralInterface.h
        algorithms/RandomWalk.cpp
        algorithms/RandomWalk.h
        Cell.h
)
target_sources(${PROJECT_NAME} PRIVATE main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE vendored)

# copies resources to build directory
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)