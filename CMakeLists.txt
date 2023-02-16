cmake_minimum_required(VERSION 3.8)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(JobySimulation
  VERSION 1.0
  LANGUAGES CXX
)

add_compile_options(-std=c++11 -Wall -Werror)

set(APP_NAME joby_sim)
set(APP_LIB_NAME joby_sim_lib)

add_subdirectory(cpputest)
add_executable(${APP_NAME} simulation_main.cpp)

