cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rtype main.cpp)

target_include_directories(rtype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rtype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(rtype PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../engine)
target_link_libraries(rtype nuts_engine)

if(MSVC)
  target_compile_options(rtype PRIVATE /W1)

  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  add_custom_command(TARGET rtype POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CONAN_BIN_DIRS_SFML}
  ${CMAKE_CURRENT_BINARY_DIR}/Debug)

  endif()