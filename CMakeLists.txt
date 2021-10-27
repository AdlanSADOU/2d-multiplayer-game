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

# copy sfml DLLs built by conan into the build directory
add_custom_command(TARGET rtype POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CONAN_BIN_DIRS_SFML}
                ${CMAKE_CURRENT_BINARY_DIR}/Debug)

# CONAN_* variables are set in conanbuildinfo.cmake
# that is generated after $>conan install
target_include_directories(rtype PUBLIC ${CONAN_INCLUDE_DIRS_SFML})
target_link_directories(rtype PUBLIC ${CONAN_LIB_DIRS_SFML})
target_link_libraries(rtype ${CONAN_LIBS_SFML})
