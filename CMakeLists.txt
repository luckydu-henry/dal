cmake_minimum_required(VERSION 3.15)

project(DAL   VERSION 1.0
              DESCRIPTION "Digital Audio Library written by modern C++20."
              LANGUAGES C CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")

file(GLOB DAL_HEADER       "include/dal/*.hpp")
file(GLOB DAL_EXT_HEADER   "include/dal/extensions/*.hpp")

source_group(dal            FILES ${DAL_HEADER})
source_group(dal/extensions FILES ${DAL_EXT_HEADER})
# This is the main part of this header only library.
add_library               (libdal INTERFACE ${DAL_HEADER} ${DAL_EXT_HEADER})
target_compile_features   (libdal INTERFACE cxx_std_20)
target_include_directories(libdal INTERFACE "include/")
# end of libdal

# Add all examples
file(GLOB EXAMPLE_SOURCES "example/*.cpp")
foreach(src ${EXAMPLE_SOURCES})
    get_filename_component(src_name ${src} NAME_WE)
    add_executable         (${src_name} ${src})
    target_compile_features(${src_name} PUBLIC cxx_std_20)
    target_link_libraries  (${src_name} PUBLIC libdal)
    set_target_properties  (${src_name} PROPERTIES FOLDER "example")
endforeach(src ${EXAMPLE_SOURCES})