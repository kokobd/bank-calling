cmake_minimum_required(VERSION 3.8)

if (TargetsWindows)
    set(CMAKE_CXX_COMPILER /usr/bin/i686-w64-mingw32-g++)
    add_definitions(-DTargetsWindows)
endif ()

project(bank-calling)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(libs/catch)

if (TargetsWindows)
    add_subdirectory(libs/mingw-std-threads)
endif ()

enable_testing()
add_subdirectory(src/app-cli)
add_subdirectory(src/service)
