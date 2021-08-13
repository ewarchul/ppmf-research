cmake_minimum_required(VERSION 3.10)

project(ppmf)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_OBJCXX_STANDARD True)

set(cmaes_target "cmaes")


find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)
set(EXTERNAL_LIBS "Threads::Threads")


file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/source/*.cpp")
file(GLOB_RECURSE INC_FILES "${PROJECT_SOURCE_DIR}/include/*.h")

add_executable(${cmaes_target} main.cpp ${SRC_FILES} ${INC_FILES})

target_link_libraries(${cmaes_target} ${EXTERNAL_LIBS})
