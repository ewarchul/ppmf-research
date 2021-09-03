cmake_minimum_required(VERSION 3.10)

project(cmaes_benchmarks)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(benchmark "benchmark")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(CLANG_DEBUG_FLAGS " -Wextra-tokens -Wambiguous-member-template -Wshadow -Wall
-pedantic -Wextra ${CODE_CONTROL_FLAGS}")

set(CLANG_RELEASE_FLAGS " -O3 -finline-functions -fmerge-all-constants
-fvectorize")

set(GCC_DEBUG_FLAGS " -O0 -g -Wshadow -Wall -pedantic -Wextra")
set(GCC_RELEASE_FLAGS " -O3 -finline-functions -fdevirtualize -fmerge-constants")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${CLANG_DEBUG_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CLANG_RELEASE_FLAGS}") 
    message(STATUS "Compiling with clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_DEBUG_FLAGS}") 
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${GCC_RELEASE_FLAGS}") 
    message(STATUS "Compiling with gcc")
endif()

find_package(LAPACK REQUIRED)

if (LAPACK_FOUND)
  set(LAPACK_LIB "${LAPACK_LIBRARIES}")
else()
  message(ERROR " Can't find LAPACK!")
endif()


add_executable(${benchmark} main.cpp)
target_link_libraries(${benchmark} ${CONAN_LIBS} ${LAPACK_LIB})

