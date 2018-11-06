cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

#In case of using cygwin, not defining win32.
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

project(app_project)

#enabling testing enviroment.
enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/algebra)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/analise)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/apoio)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/container)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/estrutura)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/geometria)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/integracao)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/malha)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/material)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/matriz)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/nos)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ponto)

add_executable(teste testes.cpp)


add_test(MakeTeste teste)

