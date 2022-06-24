cmake_minimum_required(VERSION 3.0.0)
project(Platformer VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/raylib)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME}
    "src/main.cpp"
    
    # game objects
    "src/GameObject/Bat.cpp"
    "src/GameObject/Bug.cpp"
    "src/GameObject/Coin.cpp"
    "src/GameObject/Jumper.cpp"
    "src/GameObject/KillTrigger.cpp"
    "src/GameObject/Player.cpp"
    "src/GameObject/Tile.cpp"
    "src/GameObject/Line.cpp"
    "src/GameObject/Bomb.cpp"
    "src/GameObject/Bomber.cpp"
    "src/GameObject/Goblin.cpp"

    # imgui
    "include/rlImGui/rlImGui.cpp"
    "libs/imgui/imgui.cpp"
    "libs/imgui/imgui_draw.cpp"
    "libs/imgui/imgui_tables.cpp"
    "libs/imgui/imgui_widgets.cpp"
    "libs/imgui/imgui_demo.cpp"
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/raylib/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
