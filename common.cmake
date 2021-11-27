
set(SFML_INCLUDE_DIR ../SFML/include)

# Windows
set(SFML_LIBS_DEBUG sfml-audio-d sfml-graphics-d sfml-main-d sfml-network-d sfml-system-d sfml-window-d)
set(SFML_LIBS_RELEASE sfml-audio sfml-graphics sfml-main sfml-network sfml-system sfml-window)

set(SFML_LIBS_DIR_DEBUG ../SFML/build/lib/Debug)
set(SFML_LIBS_DIR_RELEASE ../SFML/build/lib/Release)

set(SFML_EXT_LIBS_DIR ../SFML/extlibs/bin/x64)

set(EXT_DLLS openal32.dll)

set(NUTS_LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/engine/Debug/)

set(SFML_DLLS_DEBUG
sfml-audio-d-2.dll
sfml-graphics-d-2.dll
sfml-main-d-2.dll
sfml-network-d-2.dll
sfml-system-d-2.dll
sfml-window-d-2.dll)

set(SFML_DLLS_RELEASE
sfml-audio-2.dll
sfml-graphics-2.dll
sfml-main-2.dll
sfml-network-2.dll
sfml-system-2.dll
sfml-window-2.dll)

# UNIX
set(SFML_LIBS_UNIX sfml-audio.so sfml-graphics.so sfml-network.so sfml-system.so sfml-window.so)
set(SFML_LIB_DIR_UNIX ../SFML/lib)

