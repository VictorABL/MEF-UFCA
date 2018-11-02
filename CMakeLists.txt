cmake_minimum_required(VERSION 2.8)

project(app_project)

add_executable(teste testes.cpp)

install(TARGETS teste DESTINATION bin)
