cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("./common.cmake")

project(rtype VERSION 1.0)

add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)
