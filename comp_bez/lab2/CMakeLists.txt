cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

set (SOURCES main.cpp
        Cipher.cpp
        Cipher.h
        MainWindow.cpp
        MainWindow.h MainWindow.cpp MainWindow.h Binary.cpp Binary.h)

qt5_wrap_ui(UI ui/MainWindow.ui)

add_executable(lab2 ${SOURCES} ${UI})

target_link_libraries(lab2 Qt5::Core)
target_link_libraries(lab2 Qt5::Widgets)
target_link_libraries(lab2 Qt5::Quick)