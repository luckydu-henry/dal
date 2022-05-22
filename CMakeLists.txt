cmake_minimum_required(VERSION 3.0.0)
project(Musx VERSION 1.1 LANGUAGES CXX)

include(CTest)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)

include(CPack)