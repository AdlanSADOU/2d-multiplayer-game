# Installer les dependances :

```
pip install conan
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan remote add conancenter https://center.conan.io
```
---
Ajouter la ligne suivante dans le fichier ~/.conan/conan.conf en dessous de la ligne [general]
```
revisions_enabled = 1
```

# Pour compiler :

```
mkdir build
cd build
conan install .. --build=missing
cmake .. -G “Unix Makefiles”
cmake --build .
```
