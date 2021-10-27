# Remarks
- how to tell conan to build shared libs?

- no way to tell conan to pull/build x64(or amd64) libs?

- <string> must be explicitly included on windows for std::to_string

- can't pull bincrafters sfml version on windows


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
conan install .. --build=missing -s build_type=Debug
cmake .. -G "Visual Studio 16 2019" -A x86_64

cmake build static libraries:
https://cmake.org/cmake/help/latest/guide/tutorial/Selecting%20Static%20or%20Shared%20Libraries.html

- sfml version from conan only pulls "Release" static libs
  so it only compiles in release mode (or without debug info)
    - maybe we can specify in conanfile which versions we want?
        - conan install .. --build=missing -s build_type=Debug

- conan sfml package targets x86_64, but I'm using x64 compiler
    - using x86_64 for everything solved it
        - now conan builds static libraries (sfml-graphics-s-d.lib)
        but cmake generates solution with dynamic libraries (sfml-graphics-d.lib)