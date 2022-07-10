cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)
project(musx)
include_directories(${PROJECT_SOURCE_DIR}/include/)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(musx_player ${PROJECT_SOURCE_DIR}/examples/musx_player.cpp)
target_link_libraries(musx_player ${CONAN_LIBS})

add_executable(musx_audio ${PROJECT_SOURCE_DIR}/examples/musx_audio.cpp)
target_link_libraries(musx_audio ${CONAN_LIBS})