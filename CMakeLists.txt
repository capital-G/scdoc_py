cmake_minimum_required(VERSION 3.15...4.0)
project(scdoc_py LANGUAGES CXX)

set(PYTHON_PACKAGE_NAME "_scdoc_py")

add_subdirectory(external/pybind11)
pybind11_add_module(${PYTHON_PACKAGE_NAME} src/SCDoc.py.cpp)

target_sources(${PYTHON_PACKAGE_NAME} PRIVATE
    external/supercollider/SCDoc/SCDoc.cpp
    external/supercollider/SCDoc/lex.scdoc.cpp
    external/supercollider/SCDoc/SCDoc.tab.cpp
    external/supercollider/SCDoc/main.cpp
)

target_include_directories(${PYTHON_PACKAGE_NAME} PRIVATE
    external/supercollider/SCDoc
)

set_target_properties(${PYTHON_PACKAGE_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scdoc_py
)
