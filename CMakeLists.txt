
cmake_minimum_required(VERSION 3.0.0)
project(MoChengSoftRender)
set(CMAKE_CXX_STANDARD 20)

# include("D:/SomeSoft/SDL2-devel-2.26.4-mingw/SDL2-2.26.4/x86_64-w64-mingw32/lib/cmake/SDL2/sdl2-config.cmake")
# find_package(SDL2 REQUIRED)
include(cmake/sdl2-config.cmake)

include_directories(${PROJECT_SOURCE_DIR} ${SDL2_INCLUDE_DIRS})



add_subdirectory(src)
add_executable(MoChengSoftRender main.cpp)

target_link_libraries(MoChengSoftRender ${SDL2_LIBRARIES} src)
