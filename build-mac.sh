#!/bin/sh

DEBUG_DIR=build-debug
RELEASE_DIR=build-release

export CXX=g++-13
export CC=gcc-13

rm -rf $DEBUG_DIR
rm -rf $RELEASE_DIR
rm -rf vcpkg_install 
vcpkg install

cmake -B $DEBUG_DIR -DCMAKE_BUILD_TYPE=Debug --toolchain=/Users/lindemann/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build $DEBUG_DIR --config Debug

cmake -B $RELEASE_DIR -DCMAKE_BUILD_TYPE=Release --toolchain=/Users/lindemann/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build $RELEASE_DIR --config Release