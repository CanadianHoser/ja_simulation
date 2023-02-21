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

option(COMPILE_UT_HARNESS "Compile CppUTest" OFF)
if (COMPILE_UT_HARNESS)
  set(ENV{CPPUTEST_HOME} ${CMAKE_SOURCE_DIR}/cpputest)
  add_subdirectory(cpputest)
endif(COMPILE_UT_HARNESS)

option(COMPILE_TESTS "Compile the tests" ON)
if (COMPILE_TESTS)
  add_subdirectory(UnitTest)
endif(COMPILE_TESTS)

add_subdirectory(src)
