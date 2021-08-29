cmake_minimum_required(VERSION 3.10)

project(ppmf)
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

add_executable(${cmaes_target} main.cpp ${SRC_FILES} ${INC_FILES})
target_link_libraries(${cmaes_target} ${CONAN_LIBS})

add_executable(${test_target} ${TEST_FILES} ${INC_FILES})
target_link_libraries(${test_target} ${CONAN_LIBS})

include(GoogleTest)
gtest_discover_tests(${test_target})

