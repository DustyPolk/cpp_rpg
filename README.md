# Zelda-like Game

A simple top-down pixel RPG game written in C++ using raylib.

## Features
- Player character that can move in 8 directions
- Smooth movement with proper diagonal normalization
- Window boundaries to keep player on screen
- 60 FPS game loop with delta time

## Requirements
- C++17 compiler
- CMake 3.10+
- raylib 5.0+

## Building

### Ubuntu/Debian
```bash
# Install raylib dependencies
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev

# Install raylib from source
sudo apt install cmake g++
git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..
make
sudo make install
sudo ldconfig

# Build the game
cd /path/to/cpp_game
mkdir build
cd build
cmake ..
make

# Run
./ZeldaGame
```

### Windows (with vcpkg)
```bash
# Install raylib
vcpkg install raylib

# Build
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[path to vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build .

# Run
./Debug/ZeldaGame.exe
```

## Controls
- **Arrow Keys** or **WASD**: Move character
- **ESC**: Exit game