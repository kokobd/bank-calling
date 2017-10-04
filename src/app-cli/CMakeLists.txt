project(bank-calling-app VERSION 0.1 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
        src/Main.cpp
        src/Utils.h src/BankRunner.cpp src/BankRunner.h)

target_link_libraries(${PROJECT_NAME}
        bank-calling-service)