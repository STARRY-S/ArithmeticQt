cmake_minimum_required(VERSION 3.5)

project(Arithmetic LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_FLAGS "-Wall -pthread")
set(CMAKE_CXX_FLAGS ${CXX_FLAGS})

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

configure_file(images/favicon.ico images/favicon.ico COPYONLY)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.hpp
        src/arithmetic.hpp
        src/arithmetic.cpp
        src/generator.hpp
        src/generator.cpp
        src/calculator.hpp
        src/calculator.cpp
)

add_executable(
    Arithmetic
    ${PROJECT_SOURCES}
)

target_link_libraries(Arithmetic PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
