#!/bin/bash

# Build script for Tchanz Ant Simulation
# Usage: ./scripts/build.sh [options]
#   Options:
#     --debug    Build with debug symbols
#     --release  Build with optimizations
#     --clean    Clean before building
#     --verbose  Verbose output

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Default options
BUILD_TYPE="release"
CLEAN=false
VERBOSE=false

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="debug"
            shift
            ;;
        --release)
            BUILD_TYPE="release"
            shift
            ;;
        --clean)
            CLEAN=true
            shift
            ;;
        --verbose)
            VERBOSE=true
            shift
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            echo "Usage: $0 [--debug|--release] [--clean] [--verbose]"
            exit 1
            ;;
    esac
done

echo -e "${GREEN}Building Tchanz Ant Simulation (${BUILD_TYPE} mode)${NC}"

# Clean if requested
if [ "$CLEAN" = true ]; then
    echo -e "${YELLOW}Cleaning previous build...${NC}"
    make clean
fi

# Set compiler flags based on build type
if [ "$BUILD_TYPE" = "debug" ]; then
    export CXXFLAGS="-g -O0 -DDEBUG"
    echo "Building with debug symbols..."
else
    export CXXFLAGS="-O3 -DNDEBUG"
    echo "Building with optimizations..."
fi

# Build
if [ "$VERBOSE" = true ]; then
    make VERBOSE=1
else
    make
fi

# Check if build succeeded
if [ -f "projet" ]; then
    echo -e "${GREEN}Build successful!${NC}"
    echo "Executable: ./projet"
    
    # Create bin directory if it doesn't exist
    mkdir -p bin
    cp projet bin/
    
    echo -e "${GREEN}Binary copied to bin/projet${NC}"
else
    echo -e "${RED}Build failed!${NC}"
    exit 1
fi

# Run basic sanity check
echo -e "${YELLOW}Running sanity check...${NC}"
if ./projet --version 2>/dev/null | grep -q "Tchanz"; then
    echo -e "${GREEN}Sanity check passed!${NC}"
else
    echo -e "${YELLOW}Warning: Could not verify executable${NC}"
fi

echo -e "${GREEN}Build complete!${NC}"