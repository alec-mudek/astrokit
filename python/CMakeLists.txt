
cmake_minimum_required(VERSION 3.26)

project(astrokit_python LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# need to point cmake to the pybind11 cmakes
set(pybind11_DIR "C:/Users/amude/anaconda3/Lib/site-packages/pybind11/share/cmake/pybind11")

find_package(pybind11 REQUIRED CONFIG)


# Path to your astrokit headers (edit if needed)
set(ASTROKIT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../include/")


# Build a Python extension module called "astrokit"
pybind11_add_module(astrokit
    astrokit_python.cpp
    unit_structs_bindings.cpp
    constants_bindings.cpp
    math_utils_bindings.cpp
    rotations_bindings.cpp
    state_converter_bindings.cpp
    force_models_bindings.cpp)


# Tell the compiler where to find your header-only astrokit code
target_include_directories(astrokit PRIVATE ${ASTROKIT_INCLUDE_DIR})
