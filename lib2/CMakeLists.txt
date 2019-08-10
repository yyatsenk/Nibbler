cmake_minimum_required(VERSION 3.7)

project(second)

find_package(SDL2 REQUIRED)
include_directories("." "inc" "../lib1/inc" ${SDL2_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED src/lib2main.cpp)
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
message("Here is SDL  ${SDL2_LIBRARIES}")