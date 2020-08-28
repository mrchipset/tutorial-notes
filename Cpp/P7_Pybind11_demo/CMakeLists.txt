cmake_minimum_required(VERSION 3.0.0)
project(pybind11_demo VERSION 0.1.0)

 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
 
set(pybind11_DIR YOUR_PYBIND11_LIB)
find_package(pybind11 REQUIRED)
set(PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS} YOUR_INCLUDE_PATH)
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${pybind11_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})
 
 
pybind11_add_module(pybind11_demo pybind11_demo.cpp)
# include(CTest)
# enable_testing()

# add_library(pybind11_demo pybind11_demo.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
