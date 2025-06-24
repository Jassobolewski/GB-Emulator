cmake_minimum_required(VERSION 3.29)
project(GB_Emulator)
# set the output directory for built objects.
find_package(SDL3 REQUIRED)

set(CMAKE_CXX_STANDARD 23)

enable_testing()

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)


add_executable(GB_Emulator main.cpp
        SM83.cpp
        SM83.h
        MMU.h
        MMU.cpp
        AbstractInstruction.h
        Opcode.cpp
        Opcode.h)
# Link to the actual SDL3 library.
target_link_libraries(GB_Emulator PRIVATE SDL3::SDL3)

add_subdirectory(tests)