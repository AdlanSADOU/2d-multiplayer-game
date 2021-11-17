cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rtype_client
ClientMain.cpp
src/RType.cpp
src/RTypeMenu.cpp
src/RTypeNetCallbacks.cpp)

target_include_directories(rtype_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(rtype_client PUBLIC ../SFML/include)
target_link_libraries(rtype_client nuts_engine)
target_link_directories(rtype_client PUBLIC ../SFML/testBuild/lib/Debug)
target_link_libraries(rtype_client sfml-audio-d sfml-graphics-d sfml-main-d sfml-network-d sfml-system-d sfml-window-d)

if(UNIX)
  add_custom_command(TARGET rtype_client POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/../resources
  ${CMAKE_CURRENT_BINARY_DIR}/resources
  )
endif()

if(MSVC)
  target_compile_options(rtype_client PRIVATE /W1)

#   include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  add_custom_command(TARGET rtype_client POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory
#   ${CONAN_BIN_DIRS_SFML}
#   ${CMAKE_CURRENT_BINARY_DIR}/Debug

  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${CMAKE_CURRENT_SOURCE_DIR}/../resources
  ${CMAKE_CURRENT_BINARY_DIR}/Debug/resources

  )

endif()
