# Remarks

- working conan profile:
```
[settings]
os=Windows
os_build=Windows
arch=x86_64
arch_build=x86_64
compiler=Visual Studio
compiler.version=16
build_type=Debug #or Release
[options]
[build_requires]
[env]
```

# Notes
x64 == x86_64 == x86_amd64 == Amd64


conan install .. --build=missing -s build_type=Debug
cmake .. -G "Visual Studio 16 2019" -A x64


cmake build static libraries:
https://cmake.org/cmake/help/latest/guide/tutorial/Selecting%20Static%20or%20Shared%20Libraries.html

# Server Issues
server accepts same incoming connection multiple times
  [really an issue? we can just not register it]

# TODO sever
class Server
  Init()
  IsRunning()
  Listen()
  Accept()
  Dispatch()

# TODO Engine
sfml types must be typedefed by nuts or somehow encapsulated for consistency's sake

prediction
plus proche de rtype
design
sounds
