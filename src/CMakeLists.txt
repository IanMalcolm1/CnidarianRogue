set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(SourceLib STATIC
    Actor.cpp
    ActorPool.cpp
    AI.cpp
    AIStateLogic.cpp
    ConfirmerUI.cpp
    DebugLogger.cpp
    FoV.cpp
    Game.cpp
    GameLog.cpp
    GameText.cpp
    GameWindow.cpp
    GraphicsThings.cpp
    InputConfirmer.cpp
    InputManager.cpp
    Item.cpp
    LocalMap.cpp
    MapDisplay.cpp
    MapUI.cpp
    MessagesUI.cpp
    Pathfinding.cpp
    PathfindingRoute.cpp
    PlayerManager.cpp
    PlayerUI.cpp
    Scene.cpp
    SceneUI.cpp
    TerrainGenerators.cpp
    TerrainMap.cpp
    TextRenderer.cpp
    TurnQueue.cpp)

target_link_libraries(SourceLib ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
include_directories(SourceLib ${PROJECT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS})
