cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(nuts_engine
Nuts/NutsEngine.cpp
)

target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsComponents)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsSystems)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsCore)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# this is generated after $conan install
target_include_directories(nuts_engine PUBLIC ${CONAN_INCLUDE_DIRS_SFML})
target_link_directories(nuts_engine PUBLIC ${CONAN_LIB_DIRS_SFML})
target_link_libraries(nuts_engine ${CONAN_LIBS_SFML})

if(MSVC)
  target_compile_options(nuts_engine PRIVATE /W1)
endif()
