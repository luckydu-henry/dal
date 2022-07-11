#! usr/bin/sh
# Make sure your web connection is OK.

cd build
conan install .. --build-require
cmake ..
cd ..
