cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

find_package(OpenSSL REQUIRED)

set (SOURCES main.cpp
             CertificateGenerator.cpp
             CertificateGenerator.h
             MainWindow.cpp
             MainWindow.h)

qt5_wrap_ui(UI ui/MainWindow.ui)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(lab1 ${SOURCES} ${UI})

target_link_libraries(lab1 Qt5::Core)
target_link_libraries(lab1 Qt5::Widgets)
target_link_libraries(lab1 Qt5::Quick)

target_link_libraries(lab1 ${OPENSSL_LIBRARIES})