cmake_minimum_required(VERSION 3.15)

# Set project name and lang: C++
project(arrow-pybind LANGUAGES CXX)

# Break if Conda not setup/activated
if(NOT DEFINED ENV{CONDA_DEFAULT_ENV})
    message( FATAL_ERROR "(Mini)Conda enviroment required" )
elseif(NOT $ENV{CONDA_DEFAULT_ENV} STREQUAL "arrow-pybind")
    message( FATAL_ERROR "Conda environment: 'arrow-pybind' must be activated" )
endif()

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Import Apache build configs
set(Arrow_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/arrow")
set(Parquet_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/arrow")
find_package(Arrow CONFIG REQUIRED)
find_package(Parquet CONFIG REQUIRED)

# Import pybind11 build config (relative to conda-install-python)
execute_process(COMMAND python "-c" "import sys; print(sys.version[0:3], end='')" 
    OUTPUT_VARIABLE PYBIND11_PYTHON_VERSION)
message(STATUS "PYBIND11_PYTHON_VERSION: ${PYBIND11_PYTHON_VERSION}")
set(pybind11_DIR "${CMAKE_INSTALL_PREFIX}/share/cmake/pybind11")
find_package(pybind11 CONFIG REQUIRED)

# Build the pyfitparquet module (pybind11 bindings)
pybind11_add_module(pybindtest pybindtest.cc)
target_link_libraries(pybindtest PRIVATE arrow_shared parquet_shared 
    pybind11::module pybind11::lto)

