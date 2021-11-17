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
target_include_directories(rtype_server PUBLIC ${SFML_INCLUDE_DIR})
target_link_directories(rtype_server PUBLIC ${SFML_LIB_DIR_DEBUG})
target_link_libraries(rtype_server ${SFML_LIBS_DEBUG})

if(MSVC)
  target_compile_options(rtype_server PRIVATE /W1)

  file(GLOB SFML_DLLS ../SFML/build/lib/Debug/*.dll)
  foreach(myDll IN LISTS SFML_DLLS)
      add_custom_command(
          TARGET rtype_server POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different ${myDll} ${CMAKE_CURRENT_BINARY_DIR}/Debug
          COMMENT "Copy DLL: ${myDll}\n")
      endforeach()

  file(GLOB EXT_DLLS ../SFML/extlibs/bin/x64/*.dll)
  foreach(myDll IN LISTS EXT_DLLS)
      add_custom_command(
          TARGET rtype_server POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different ${myDll} ${CMAKE_CURRENT_BINARY_DIR}/Debug
          COMMENT "Copy DLL: ${myDll}\n")
      endforeach()
endif()
