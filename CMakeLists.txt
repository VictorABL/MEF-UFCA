cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(app_project)

enable_testing()


add_executable(teste testes.cpp)

add_test(MakeTeste teste)

