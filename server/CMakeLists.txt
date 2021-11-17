cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rtype_server
ServerMain.cpp
)

target_include_directories(rtype_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rtype_server nuts_engine)

if(MSVC)
  target_compile_options(rtype_server PRIVATE /W1)

  target_include_directories(rtype_server PUBLIC ../SFML/include)
  target_link_directories(rtype_server PUBLIC ../SFML/testBuild/lib/Debug)
  target_link_libraries(rtype_server sfml-audio-d sfml-graphics-d sfml-main-d sfml-network-d sfml-system-d sfml-window-d)

#   add_custom_command(TARGET rtype_server POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#   ${CONAN_BIN_DIRS_SFML}
#   ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endif()
