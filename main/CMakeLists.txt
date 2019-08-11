cmake_minimum_required(VERSION 3.7)

project(SDL2Test)

include_directories("."  "../lib1/inc" "../lib1" "../lib2/inc" "inc" ${SDL2_INCLUDE_DIRS})

add_executable(SDL2Test src/main.cpp)
target_link_libraries(SDL2Test first  dl)
message("Here is SDL  ${SDL2_LIBRARIES}")
