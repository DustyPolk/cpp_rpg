cmake_minimum_required(VERSION 3.10)
project(ZeldaGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find raylib
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

# Include directories
include_directories(include config)
include_directories(${RAYLIB_INCLUDE_DIRS})

# Source files
set(SOURCES
    src/main.cpp

    src/core/Game.cpp

    src/entities/Player.cpp
    src/entities/Wall.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link raylib
target_link_libraries(${PROJECT_NAME} ${RAYLIB_LIBRARIES})
target_link_directories(${PROJECT_NAME} PUBLIC ${RAYLIB_LIBRARY_DIRS})
target_compile_options(${PROJECT_NAME} PUBLIC ${RAYLIB_CFLAGS_OTHER})

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})