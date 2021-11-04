cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rtype_client ClientMain.cpp)

target_include_directories(rtype_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rtype_client nuts_engine)

if(MSVC)
  target_compile_options(rtype_client PRIVATE /W1)

  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  add_custom_command(TARGET rtype_client POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CONAN_BIN_DIRS_SFML}
  ${CMAKE_CURRENT_BINARY_DIR}/Debug

  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/../resources
  ${CMAKE_CURRENT_BINARY_DIR}/Debug/resources

  )

endif()
