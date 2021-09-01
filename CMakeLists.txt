cmake_minimum_required(VERSION 3.10)

project(ppmf)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(cmaes_target "cmaes")
set(test_target "cmaes_test")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/source/*.cpp")
file(GLOB_RECURSE INC_FILES "${PROJECT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE TEST_FILES "${PROJECT_SOURCE_DIR}/tests/*.cpp")


set(CLANG_DEBUG_FLAGS " -Wextra-tokens -Wambiguous-member-template -Wshadow -Wall
-pedantic -Wextra ${CODE_CONTROL_FLAGS}")

set(CLANG_RELEASE_FLAGS " -O3 -finline-functions -fmerge-all-constants
-fvectorize")

set(GCC_DEBUG_FLAGS " -O0 -g -Wshadow -Wall -pedantic -Wextra")
set(GCC_RELEASE_FLAGS " -O3 -finline-functions -fdevirtualize -fmerge-constants")


if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${CLANG_DEBUG_FLAGS}")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CLANG_RELEASE_FLAGS}") 
    message(STATUS "Compiling with clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_DEBUG_FLAGS}") 
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${GCC_RELEASE_FLAGS}") 
    message(STATUS "Compiling with gcc")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})


add_executable(${cmaes_target} main.cpp ${SRC_FILES} ${INC_FILES})
target_link_libraries(${cmaes_target} ${CONAN_LIBS})

add_executable(${test_target} ${TEST_FILES} ${INC_FILES} ${SRC_FILES})
target_link_libraries(${test_target} ${CONAN_LIBS})

add_test(NAME cmaes_test COMMAND
  "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${test_target}")

