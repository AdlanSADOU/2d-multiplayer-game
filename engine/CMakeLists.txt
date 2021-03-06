cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/Debug")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/Debug")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/client/Debug")
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/server/Debug")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_library(nuts_engine
Nuts/Engine.cpp
)

set_target_properties(nuts_engine PROPERTIES
POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})

target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsComponents)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsSystems)
target_include_directories(nuts_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Nuts/EcsCore)

target_include_directories(nuts_engine PUBLIC ${SFML_INCLUDE_DIR})

if(MSVC)

target_compile_options(nuts_engine PRIVATE /W3)
target_link_directories(nuts_engine PUBLIC ${SFML_LIBS_DIR_DEBUG})
target_link_libraries(nuts_engine ${SFML_LIBS_DEBUG})

elseif(UNIX)

target_link_directories(nuts_engine PUBLIC ${SFML_LIB_DIR_UNIX})
target_link_libraries(nuts_engine ${SFML_LIBS_UNIX})

endif()
