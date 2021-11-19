cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(nuts_engine
Nuts/Engine.cpp
)

target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsComponents)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsSystems)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsCore)

target_include_directories(nuts_engine PUBLIC ${SFML_INCLUDE_DIR})
target_link_directories(nuts_engine PUBLIC ${SFML_LIBS_DIR_RELEASE})

if(MSVC)
    target_compile_options(nuts_engine PRIVATE /W3)
    target_link_libraries(nuts_engine ${SFML_LIBS_RELEASE})
elseif(UNIX)
    target_link_libraries(nuts_engine ${SFML_LIBS_UNIX})
endif()