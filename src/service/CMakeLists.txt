project(bank-calling-service VERSION 0.1 LANGUAGES CXX)

add_library(${PROJECT_NAME}
        include/bank-calling/service/Bank.h
        src/Bank.cpp

        include/bank-calling/service/Customer.h
        src/Customer.cpp

        include/bank-calling/service/Window.h
        src/Window.cpp

        include/bank-calling/service/RandomGen.h
        src/RandomGen.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        private src)

if (TargetsWindows)
    target_link_libraries(${PROJECT_NAME}
            mingw-std-threads)
endif ()

add_executable(${PROJECT_NAME}-test
        test/TestMain.cpp
        test/CustomerTest.cpp
        test/WindowTest.cpp
        test/BankTest.cpp
        )
target_link_libraries(${PROJECT_NAME}-test
        catch
        ${PROJECT_NAME})