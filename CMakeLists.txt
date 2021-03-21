cmake_minimum_required(VERSION 3.15)
project(Thermal_conduction LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

find_package(MPI REQUIRED)
include_directories(lib)

add_executable(non_Block.exe src/main_non_Block.cpp)
target_link_libraries(non_Block.exe MPI::MPI_CXX)

add_executable(Block.exe src/main_Block.cpp)
target_link_libraries(Block.exe MPI::MPI_CXX)
