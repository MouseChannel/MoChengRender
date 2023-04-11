
cmake_minimum_required(VERSION 3.0.0)
project(MoChengSoftRender)
set(CMAKE_CXX_STANDARD 20)

 
include(cmake/sdl2-config.cmake)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})

add_subdirectory(src)
add_executable(MoChengSoftRender main.cpp)

target_link_libraries(MoChengSoftRender ${SDL2_LIBRARIES} src)
