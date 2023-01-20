cmake_minimum_required(VERSION 3.5)

project(TCC_ControleDeMaquina LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    QT NAMES Qt6
    Qt5 Core SerialPort
    COMPONENTS Widgets LinguistTools
    REQUIRED)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
    Widgets
    Core SerialPort
    LinguistTools
    REQUIRED)

set(TS_FILES TCC_ControleDeMaquina_pt_BR.ts)

set(PROJECT_SOURCES
        main.cpp
        # main
        mainwindow.cpp
        mainwindow.hpp
        mainwindow.ui
        # home
        homedevice.cpp
        homedevice.hpp
        homedevice.ui
        # serialport
        serialport.hpp
        serialport.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TCC_ControleDeMaquina
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(TCC_ControleDeMaquina SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(TCC_ControleDeMaquina
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(TCC_ControleDeMaquina PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::SerialPort
    )
