cmake_minimum_required(VERSION 3.8)
project(bank-calling)

set(CMAKE_CXX_STANDARD 14)

set(wxWidgets_ROOT_DIR libs/wxWidgets-3.0.3)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets REQUIRED
        COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_subdirectory(libs/catch)

enable_testing()
add_subdirectory(src/app)
add_subdirectory(src/service)
