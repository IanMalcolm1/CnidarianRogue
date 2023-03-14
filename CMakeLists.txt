cmake_minimum_required(VERSION 3.16)

project(Roguelike LANGUAGES CXX)

add_subdirectory(src)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(Roguelike main.cpp)

set_property(TARGET Roguelike PROPERTY CXX_STANDARD 20)

target_link_libraries(Roguelike 
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
    SourceLib)

include_directories(Roguelike 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include)
