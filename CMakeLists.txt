cmake_minimum_required(VERSION 3.21)
project(openmpi_porgramming C)

##set(CMAKE_C_STANDARD 99)
##add_executable(openmpi_porgramming main.c)


find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()