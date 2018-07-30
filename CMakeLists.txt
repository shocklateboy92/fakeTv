cmake_minimum_required(VERSION 2.8)

project(fakeTv2)
enable_language(CXX)

add_executable(${PROJECT_NAME} main.cpp utils.h utils.cpp callbacks.h callbacks.cpp)
target_link_libraries(fakeTv2 dl)
