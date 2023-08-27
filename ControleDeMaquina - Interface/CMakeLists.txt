cmake_minimum_required(VERSION 3.5)

project(ControleDeMaquina LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    QT
    NAMES
    Qt5
    Core
    SerialPort
    COMPONENTS
    Widgets
    REQUIRED)

find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
    Widgets
    Core
    SerialPort
    REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
    src/TelaInicial/mainwindow.cpp
    src/AreaDeControle/areadecontrole.cpp
    src/ComunicacaoSerial/serialport.cpp
    )

set(PROJECTS_UIS
    ui/mainwindow.ui
    ui/areadecontrole.ui
    )

set(PROJECT_HEADERS
    src/TelaInicial/mainwindow.hpp
    src/AreaDeControle/areadecontrole.hpp
    src/ComunicacaoSerial/serialport.hpp
    )

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${PROJECT_SOURCE_DIR}/ui
    )

add_executable(ControleDeMaquina
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECTS_UIS}
    )

target_link_libraries(ControleDeMaquina PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::SerialPort
    )
