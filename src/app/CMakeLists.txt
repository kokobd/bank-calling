project(bank-calling-app)

execute_process(COMMAND wx-config --libs adv base core OUTPUT_VARIABLE wxWidgets_LIBRARIES OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND wx-config --cxxflags adv base core OUTPUT_VARIABLE wxFlags OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${wxFlags}")

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
        src/gui/InfoUpdateEvent.h
        src/gui/InfoUpdateEvent.cpp
        )
target_link_libraries(${PROJECT_NAME}
        ${wxWidgets_LIBRARIES}
        bank-calling-service)
if (TargetsWindows)
    target_link_libraries(${PROJECT_NAME}
            mingw-std-threads)
endif ()
