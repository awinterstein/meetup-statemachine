#!/bin/bash

SOURCE_DIR="$( cd "$(dirname "$0")" ; pwd -P )"
BUILD_DIR=${1:-"${SOURCE_DIR}/../build"}

mkdir -p "$BUILD_DIR"
pushd "$BUILD_DIR"
export ARMGCC_DIR=/usr/local/mcuxpressoide-10.2.0_759/ide/tools/

cmake "$SOURCE_DIR" -DCMAKE_TOOLCHAIN_FILE="$SOURCE_DIR/cmake/armgcc.cmake" -G"Eclipse CDT4 - Ninja" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_ECLIPSE_VERSION=4.7 -DCMAKE_ECLIPSE_GENERATE_LINKED_RESOURCES=OFF
popd

