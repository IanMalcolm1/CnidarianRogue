set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Roguelike
   main.cpp
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

set_property(TARGET Roguelike PROPERTY CXX_STANDARD 20)

target_link_libraries(Roguelike ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
include_directories(Roguelike ${PROJECT_SOURCE_DIR}/include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS})
