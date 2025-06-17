#!/bin/bash

# Install script for ZeldaGame dependencies on Ubuntu/Debian
# This script installs CMake, raylib, and all required dependencies

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}==========================================${NC}"
echo -e "${BLUE}    ZeldaGame Dependency Installer${NC}"
echo -e "${BLUE}==========================================${NC}"
echo ""

# Function to check if running with sudo
check_sudo() {
    if [ "$EUID" -ne 0 ]; then 
        echo -e "${RED}This script needs to be run with sudo${NC}"
        echo -e "${YELLOW}Usage: sudo ./install_dependencies.sh${NC}"
        exit 1
    fi
}

# Function to print status
print_status() {
    echo -e "${YELLOW}[*] $1${NC}"
}

print_success() {
    echo -e "${GREEN}[✓] $1${NC}"
}

print_error() {
    echo -e "${RED}[✗] $1${NC}"
}

# Check for sudo
check_sudo

# Update package list
print_status "Updating package list..."
apt update
print_success "Package list updated"

# Install build essentials and CMake
print_status "Installing build tools and CMake..."
apt install -y build-essential cmake git
print_success "Build tools and CMake installed"

# Install raylib dependencies
print_status "Installing raylib dependencies..."
apt install -y \
    libasound2-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxcursor-dev \
    libxinerama-dev \
    libwayland-dev \
    libxkbcommon-dev
print_success "Raylib dependencies installed"

# Check if raylib is available in package manager
print_status "Checking for raylib in package manager..."
if apt-cache show libraylib-dev &> /dev/null; then
    print_status "Installing raylib from package manager..."
    apt install -y libraylib-dev
    print_success "Raylib installed from package manager"
else
    print_status "Raylib not found in package manager, building from source..."
    
    # Create temporary directory for building
    TEMP_DIR=$(mktemp -d)
    cd $TEMP_DIR
    
    # Clone raylib
    print_status "Cloning raylib repository..."
    git clone https://github.com/raysan5/raylib.git
    cd raylib
    
    # Build raylib
    print_status "Building raylib..."
    mkdir build && cd build
    cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Release ..
    make -j$(nproc)
    
    # Install raylib
    print_status "Installing raylib..."
    make install
    ldconfig
    
    # Cleanup
    cd /
    rm -rf $TEMP_DIR
    
    print_success "Raylib built and installed from source"
fi

# Verify installations
echo ""
echo -e "${BLUE}Verifying installations...${NC}"

# Check CMake
if command -v cmake &> /dev/null; then
    CMAKE_VERSION=$(cmake --version | head -n1)
    print_success "CMake: $CMAKE_VERSION"
else
    print_error "CMake installation failed"
fi

# Check g++
if command -v g++ &> /dev/null; then
    GCC_VERSION=$(g++ --version | head -n1)
    print_success "G++: $GCC_VERSION"
else
    print_error "G++ installation failed"
fi

# Check raylib
if pkg-config --exists raylib 2>/dev/null; then
    RAYLIB_VERSION=$(pkg-config --modversion raylib 2>/dev/null || echo "installed")
    print_success "Raylib: $RAYLIB_VERSION"
elif [ -f /usr/local/lib/libraylib.so ] || [ -f /usr/lib/libraylib.so ]; then
    print_success "Raylib: installed (library found)"
else
    print_error "Raylib installation may have issues"
fi

echo ""
echo -e "${GREEN}==========================================${NC}"
echo -e "${GREEN}    Installation Complete!${NC}"
echo -e "${GREEN}==========================================${NC}"
echo ""
echo -e "${BLUE}You can now build the game with:${NC}"
echo -e "  ${YELLOW}./build.sh${NC}"
echo ""
echo -e "${BLUE}Or manually with:${NC}"
echo -e "  ${YELLOW}mkdir -p build && cd build${NC}"
echo -e "  ${YELLOW}cmake ..${NC}"
echo -e "  ${YELLOW}make${NC}"
echo -e "  ${YELLOW}./ZeldaGame${NC}"
echo ""