# R-Type

## Installer les dependances

```console
sudo dnf install openal-soft-devel.x86_64 && libvorbis-devel.x86_64 &&flac-devel.x86_64

git submodule init
git submodule update

```

<!--
```console
pip install conan
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
conan remote add conancenter https://center.conan.io
```

---
Ajouter la ligne suivante dans le fichier ~/.conan/conan.conf en dessous de la ligne [general]

```console
revisions_enabled = 1
``` -->

## Pour compiler

```console
cd SFML
cmake -G “Unix Makefiles”
cmake --build .
```

## Pour ne pas track SFML dans l'extension Git

Ajoutez ces 2 lignes dans ```.vscode/settings.json```
```json
    "git.ignoreSubmodules": true,
    "git.ignoredRepositories": ["SFML"],
```