#!/bin/bash

# Build script for ZeldaGame
# Usage: ./build.sh [clean]

set -e  # Exit on any error

BUILD_DIR="build"
PROJECT_NAME="ZeldaGame"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== ZeldaGame Build Script ===${NC}"

# Check if clean build is requested
if [ "$1" == "clean" ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf $BUILD_DIR
fi

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
    echo -e "${YELLOW}Creating build directory...${NC}"
    mkdir -p $BUILD_DIR
fi

# Change to build directory
cd $BUILD_DIR

# Configure with CMake
echo -e "${YELLOW}Configuring project with CMake...${NC}"
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the project
echo -e "${YELLOW}Building project...${NC}"
make -j$(nproc)

echo -e "${GREEN}Build completed successfully!${NC}"
echo -e "${GREEN}Executable: ${BUILD_DIR}/${PROJECT_NAME}${NC}"
echo -e "${GREEN}To run: cd ${BUILD_DIR} && ./${PROJECT_NAME}${NC}" 