cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(rtype VERSION 1.0)

add_subdirectory(Engine)
add_subdirectory(Client)
add_subdirectory(Server)