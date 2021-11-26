cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
if (UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -lpthread")
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rtype_server
ServerMain.cpp
Imgui/imgui-SFML.cpp
Imgui/imgui_draw.cpp
Imgui/imgui_tables.cpp
Imgui/imgui_widgets.cpp
Imgui/imgui.cpp
)

target_include_directories(rtype_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(rtype_server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Imgui)

target_link_libraries(rtype_server nuts_engine opengl32)
target_include_directories(rtype_server PUBLIC ${SFML_INCLUDE_DIR})

if(MSVC)
target_compile_options(rtype_server PRIVATE /W3)
    target_link_directories(rtype_server PUBLIC ${SFML_LIBS_DIR_DEBUG})
    target_link_libraries(rtype_server ${SFML_LIBS_DEBUG})

    file(GLOB SFML_DLLS_DEBUG "${SFML_LIBS_DIR_DEBUG}/*.dll")
    foreach(myDll IN LISTS SFML_DLLS_DEBUG)
        add_custom_command(
            TARGET rtype_server POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${myDll} ${CMAKE_CURRENT_BINARY_DIR}/Debug
            COMMENT "Copy DLL: ${myDll}\n")
        endforeach()

    file(GLOB EXT_DLLS "${SFML_EXT_LIBS_DIR}/*.dll")
    foreach(myDll IN LISTS EXT_DLLS)
        add_custom_command(
            TARGET rtype_server POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different ${myDll} ${CMAKE_CURRENT_BINARY_DIR}/Debug
            COMMENT "Copy DLL: ${myDll}\n")
        endforeach()

elseif(UNIX)
    target_link_directories(rtype_server PUBLIC ${SFML_LIB_DIR_UNIX})
    target_link_libraries(rtype_server ${SFML_LIBS_UNIX})
endif()
