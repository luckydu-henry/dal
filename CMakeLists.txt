cmake_minimum_required(VERSION 3.15)

project(DAL   VERSION 1.0
              DESCRIPTION "Digital Audio Library written by modern C++20."
              LANGUAGES C CXX)

file(GLOB DAL_HEADER       "include/dal/*.hpp")
file(GLOB DAL_EXT_HEADER   "include/dal/extensions/*.hpp")

set(INC_PATH "include/")
source_group(dal            FILES ${DAL_HEADER})
source_group(dal/extensions FILES ${DAL_EXT_HEADER})

# This example shows how to sample from an oscillator and write sampled pcm to a fstream.
add_executable            (sample_and_to_file "example/sample_and_to_file.cpp" ${DAL_HEADER} ${DAL_EXT_HEADER})
target_compile_features   (sample_and_to_file PUBLIC cxx_std_20)
target_include_directories(sample_and_to_file PUBLIC ${INC_PATH})

# This example shows how to read and write an wave file using io extension.
add_executable            (read_wave_and_to_file "example/read_wave_and_to_file.cpp" ${DAL_HEADER} ${DAL_EXT_HEADER})
target_compile_features   (read_wave_and_to_file PUBLIC cxx_std_20)
target_include_directories(read_wave_and_to_file PUBLIC ${INC_PATH})