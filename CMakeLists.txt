cmake_minimum_required(VERSION 3.5)

project(TCC_ControleDeMaquina LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(
    QT
    NAMES
    Qt6
    Qt5
    Core
    SerialPort
    COMPONENTS
    Widgets
    LinguistTools
    REQUIRED)

find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
    Widgets
    Core
    SerialPort
    LinguistTools
    REQUIRED)

set(TS_FILES
    libs/ts/TCC_ControleDeMaquina_pt_BR.ts
    )

set(PROJECT_SOURCES
    src/main.cpp
    src/TelaInicial/mainwindow.cpp
    src/AreaDeControle/homedevice.cpp
    src/ComunicacaoSerial/serialport.cpp
    )

set(PROJECTS_UIS
    libs/ui/mainwindow.ui
    libs/ui/homedevice.ui
    )

set(PROJECT_HEADERS
    src/TelaInicial/mainwindow.hpp
    src/AreaDeControle/homedevice.hpp
    src/ComunicacaoSerial/serialport.hpp
    )

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${PROJECT_SOURCE_DIR}/libs/ui
    )

add_executable(TCC_ControleDeMaquina
    ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECTS_UIS} ${TS_FILES}
    )

target_link_libraries(TCC_ControleDeMaquina PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::SerialPort
    )
