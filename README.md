# R-Type

This project was an attempt at writing a LAN multiplayer 2D game in a month, with up to 4 players (technically the server can handle more than 100 players on a single instance).
It is a Client/Server architecture, features an ECS (Entity Component System) and a generic Event system.

## Install dependencies

On linux, the following development libraries are needed in order to build SFML:
(non exhaustive list)
- openal
- libvorbis
- flac

while cloning this repository :
```console
git clone --recursive [url]

    or

git submodule init
git submodule update

```

## Windows build

```console
cd SFML
cmake -A x64 -B build/
cmake --build build/

cd ..
cmake -A x64 -B build/
cmake --build build/

```

## Linux build

```console
cd SFML
cmake -G "Unix Makefiles" -B build/
cmake --build build/

cd ..
cmake -G "Unix Makefiles" -B build/
cmake --build build/
```

## To avoid tracking git submodule changes in vscode

Add these lines in ```.vscode/settings.json```
```json
    ...
    "git.ignoreSubmodules": true,
    "git.ignoredRepositories": ["SFML"],
```
