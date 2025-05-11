#!/bin/bash

# Sudoku Solver Build Script

# Stop on first error
set -e

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Configure CMake with Clang
export CC=clang
export CXX=clang++
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build the project using all available cores
cmake --build . -- -j$(nproc)

# Return to project root
cd ..

# Run tests if requested
if [ "$1" == "--test" ]; then
    cd build
    ctest --output-on-failure
    cd ..
fi

echo ""
echo "Build completed successfully!"
echo "To run the application: ./build/sudoku_solver"
echo ""
