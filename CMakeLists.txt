cmake_minimum_required(VERSION 3.5)

project(Arthmetic LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

configure_file(images/favicon.ico images/favicon.ico COPYONLY)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/arthmetic.h
        src/arthmetic.cpp
)

add_executable(
    Arthmetic
    ${PROJECT_SOURCES}
)

target_link_libraries(Arthmetic PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
