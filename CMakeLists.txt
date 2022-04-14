cmake_minimum_required(VERSION 3.21)
project(openmpi_porgramming C)

set(CMAKE_C_STANDARD 99)
add_executable(openmpi_porgramming main.c)


#[[
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()]]


#[[

cmake_minimum_required(VERSION 3.21)
project(openmpi_porgramming)

set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(openmpi_porgramming main.c)

target_link_libraries(openmpi_porgramming ${MPI_C_LIBRARIES})]]
