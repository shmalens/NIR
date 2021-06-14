cmake_minimum_required(VERSION 3.16)
project(polygonal)

set(CMAKE_CXX_STANDARD 17)

add_executable(polygonal project/main.cpp)
include_directories(project/include)

add_library(polygonal_lib STATIC project/src/PolygonalNumber.cpp
                                 project/src/WindowManager.cpp)

target_link_libraries(polygonal polygonal_lib)
target_link_libraries(polygonal m)
target_link_libraries(polygonal sfml-window)
target_link_libraries(polygonal sfml-system)
target_link_libraries(polygonal sfml-graphics)
