cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(lab3 main.cpp)

target_link_libraries(lab3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})