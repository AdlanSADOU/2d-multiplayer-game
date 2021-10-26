cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(rtype VERSION 1.0)

add_executable(rtype main.cpp src/Pig.cpp)
target_include_directories(rtype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(rtype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)