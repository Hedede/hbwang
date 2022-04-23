cmake_minimum_required(VERSION 3.5)

project(hbwang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/*.h)


add_executable(hbwang main.cpp ${HEADERS})
target_include_directories(hbwang PRIVATE ${PROJECT_SOURCE_DIR})
