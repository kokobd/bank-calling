project(catch VERSION 0.1 LANGUAGES CXX)

add_library(catch INTERFACE)

target_include_directories(catch INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/>)

#install(TARGETS catch EXPORT CatchConfig)
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
#install(EXPORT CatchConfig DESTINATION share/catch/cmake)
#export(TARGETS catch FILE catch.cmake)