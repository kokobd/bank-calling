project(bank-calling-app)

add_executable(${PROJECT_NAME}
        src/Main.h
        src/Main.cpp
        src/gui/MainFrame.h
        src/gui/MainFrame.cpp
        src/gui/DataPanel.h
        src/gui/DataPanel.cpp
        src/gui/ControlPanel.h
        src/gui/ControlPanel.cpp
        src/BankRunner.h
        src/BankRunner.cpp
        )
target_link_libraries(${PROJECT_NAME}
        ${wxWidgets_LIBRARIES}
        bank-calling-service)

