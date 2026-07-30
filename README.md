# Sumotori Dreams

## Building

Requirements:

- CMake
- [VS2003](https://github.com/archaic-msvc/msvc710)

From the repository root, run the following commands:

```bat
cmake -S . -B build -G "NMake Makefiles"
cmake --build build
```

The resulting executables are `build\sumofull.exe` and
`build\sumoeditor.exe`.

The full game is enabled by default. To build the demo
behavior instead, configure with:

```bat
cmake -S . -B build-demo -G "NMake Makefiles" -DSUMO_REGISTERED_BUILD=OFF
cmake --build build-demo
```
