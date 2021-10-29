cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(rtype VERSION 1.0)

add_subdirectory(engine)
add_subdirectory(client)
add_subdirectory(server)
