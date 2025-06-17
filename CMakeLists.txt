cmake_minimum_required(VERSION 3.29)
project(GB_Emulator)
# set the output directory for built objects.
find_package(SDL3)

set(CMAKE_CXX_STANDARD 23)

add_executable(GB_Emulator main.cpp)
# Link to the actual SDL3 library.
target_link_libraries(GB_Emulator PRIVATE SDL3::SDL3)