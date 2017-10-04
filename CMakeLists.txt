cmake_minimum_required(VERSION 3.8)

if (TargetsWindows)
    set(CMAKE_CXX_COMPILER /usr/bin/i686-w64-mingw32-g++)
    add_definitions(-DTargetsWindows)
endif ()

project(bank-calling)

set(CMAKE_CXX_STANDARD 14)

#set(wxWidgets_USE_UNICODE)
#set(wxWidgets_USE_STATIC)
#set(wxWidgets_ROOT_DIR ${CMAKE_SOURCE_DIR}/libs/wxWidgets)
#set(exWidgets_LIB_DIR ${CMAKE_SOURCE_DIR}/libs/wxWidgets/gtk-build/lib)
#set(wxWidgets_CONFIGURATION mswu)
#find_package(wxWidgets REQUIRED
#        COMPONENTS core base adv)
#include(${wxWidgets_USE_FILE})
#message(${wxWidgets_LIBRARY_DIRS})

add_subdirectory(libs/catch)

if (TargetsWindows)
    add_subdirectory(libs/mingw-std-threads)
endif ()

enable_testing()
add_subdirectory(src/app)
add_subdirectory(src/service)
