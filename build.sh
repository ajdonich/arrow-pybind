#!/bin/bash

set -e

THIS_SCRIPT=$(basename $0)
if [ ! -f "$THIS_SCRIPT" ]; then
    echo "ERROR: must execute this script from arrow-crash root directory"
    echo
    exit 1
fi

: ${ARROW_PYBIND_ROOT:=${PWD}}
: ${ARROW_CPP:=${ARROW_PYBIND_ROOT}/arrow/cpp}
: ${ARROW_INSTALL:=${ARROW_CPP}/arrow-install}

if [ ! -d "$ARROW_CPP" ]; then
    echo
    echo "=="
    echo "== Cloning Apache Arrow C++ repo"
    echo "=="
    echo
    git clone https://github.com/apache/arrow.git
fi

echo
echo "=="
echo "== Building Arrow C++ library"
echo "=="
echo
cd $ARROW_CPP
cmake -H. -Barrow-build \
    -DARROW_BUILD_STATIC=OFF \
    -DARROW_BUILD_SHARED=ON \
    -DARROW_PARQUET=ON \
    -DARROW_WITH_SNAPPY=ON \
    -DARROW_BUILD_EXAMPLES=OFF \
    -DPARQUET_BUILD_EXAMPLES=OFF \
    -DCMAKE_INSTALL_PREFIX=${ARROW_INSTALL}

cmake --build arrow-build --target install

echo
echo "=="
echo "== Building Python module"
echo "=="
echo
cd $ARROW_PYBIND_ROOT
cmake -H. -B_build \
    -DCMAKE_PREFIX_PATH=${CONDA_PREFIX} \
    -DCMAKE_INSTALL_PREFIX=${ARROW_INSTALL} 

cmake --build _build
cp ./pybindtest.py _build/.
