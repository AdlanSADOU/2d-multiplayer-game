# Installer les dependances :

```
pip install conan
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan remote add conancenter https://center.conan.io
```

# Pour compiler :

```
mkdir build
cd build
conan install .. --build=missing
cmake .. -G “Unix Makefiles”
cmake --build .
```
