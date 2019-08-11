cmake_minimum_required(VERSION 3.7)

project(first)

find_package(SDL2 REQUIRED)
include_directories("."  "inc" "../main/inc" ${SDL2_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED src/maintain.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
message("Here is SDL  ${SDL2_LIBRARIES}")