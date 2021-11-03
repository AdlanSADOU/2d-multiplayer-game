[![CMake](https://github.com/EpitechPromo2024/B-CPP-501-NCE-5-1-rtype-adlan.sadou/actions/workflows/cmake.yml/badge.svg)](https://github.com/EpitechPromo2024/B-CPP-501-NCE-5-1-rtype-adlan.sadou/actions/workflows/cmake.yml)

# R-Type

## Installer les dependances

```console
pip install conan
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan remote add conancenter https://center.conan.io
```

---
Ajouter la ligne suivante dans le fichier ~/.conan/conan.conf en dessous de la ligne [general]

```console
revisions_enabled = 1
```

## Pour compiler

```console
mkdir build
cd build
conan install .. --build=missing
cmake .. -G “Unix Makefiles”
cmake --build .
```
