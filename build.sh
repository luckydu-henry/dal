#! usr/bin/sh

cd build
conan install .. --build-require
cmake ..