cmake_minimum_required(VERSION 3.0.2)
project (AppTransport)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
include_directories("${PROJECT_SOURCE_DIR}")
set(CMAKE_C_FLAGS "-std=c11 -Wall")
add_executable(app_transport ${PROJECT_SOURCE_DIR}/app_transport.c ${PROJECT_SOURCE_DIR}/menu.c  ${PROJECT_SOURCE_DIR}/pass.c  ${PROJECT_SOURCE_DIR}/trans.c)

