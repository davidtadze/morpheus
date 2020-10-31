# morpheus

simple 3d software rasterizer

# setup

assuming mac os, vscode and following project structure:

```
.
├── .gitignore
├── README.md
└── src
    └── main.cpp
```

## cmake

for managing the build process

1. install `cmake`:

   ```
   brew install cmake
   ```

2. create `CMakeLists.txt` in project root folder:

   ```cmake
   cmake_minimum_required(VERSION 3.18.0)

   project(morpheus)

   set(CMAKE_CXX_STANDARD 11)
   set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

   # enable warnings (as per https://stackoverflow.com/a/14235055).
   if (CMAKE_COMPILER_IS_GNUCC)
     set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
   endif (CMAKE_COMPILER_IS_GNUCC)

   file(GLOB SOURCES "src/*.cpp")
   add_executable(morpheus ${SOURCES})
   ```

to reduce clutter, create a `build` folder in project root folder. to build the project, run the following commands from within `build` folder:

1. `cmake ../`

2. `make`

## clangd

for c++ language support 

1. install [clangd](https://marketplace.visualstudio.com/items?itemName=llvm-vs-code-extensions.vscode-clangd) extension

2. make sure you have the following line in your `CmakeLists.txt`: `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)`

3. after building your project (see above), create a `compile_commands.json` symlink. to do so, run the following command from within the project root folder (assuming you created the `build` folder to reduce clutter):

   `ln -s build/compile_commands.json compile_commands.json`

to enable `clang-tidy` checks create a `.clang-tidy` file in the project root folder:

```
Checks: 'bugprone-*, clang-diagnostic-*, clang-analyzer-*,
    cppcoreguidelines-*, google-*, misc-*,
    modernize-*, performance-*, portability-*,
    readability-*'
FormatStyle: google
```

## .gitignore

don't forget to add the following lines to  `.gitignore`:

```
.DS_Store

build/*

.clangd
.clang-tidy
.clang-format
compile_commands.json
```

