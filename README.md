# Sudoku Solver

A C++ implementation of a Sudoku puzzle solver using the backtracking algorithm.

## Features

- Solve any valid 9x9 Sudoku puzzle
- Interactive command-line interface
- Load/save puzzles from/to files
- Sample puzzle included for quick testing
- Input validation
- Multi-file project structure with CMake build system

## Requirements

- C++17 compatible compiler (Clang recommended)
- CMake (minimum version 3.10)
- Google Test (optional, for running tests - automatically downloaded by CMake)

## Project Structure

```
SudokuProject/
├── CMakeLists.txt          # CMake build configuration
├── include/
│   └── SudokuSolver.hpp    # Header file with class declaration
├── src/
│   ├── main.cpp            # Main application entry point
│   └── SudokuSolver.cpp    # Implementation of the Sudoku solver
├── tests/
│   └── test_sudoku.cpp     # Test suite using Google Test
└── README.md               # This file
```

## Building the Project

### Using the Build Script

```bash
# Make the build script executable
chmod +x build.sh

# Build the project
./build.sh

# Build and run tests
./build.sh --test
```

### Manual Build

```bash
# Create a build directory
mkdir -p build
cd build

# Configure with CMake using Clang
export CC=clang
export CXX=clang++
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build the project
cmake --build .

# Run the application
./sudoku_solver
```

### Building with Tests

To build with tests enabled:

```bash
mkdir -p build
cd build
cmake -DBUILD_TESTS=ON ..
cmake --build .
```

Run the tests:
```bash
ctest --output-on-failure
```

## Usage

The application provides an interactive menu with the following options:

1. **Load sample puzzle**: Loads a predefined Sudoku puzzle
2. **Enter puzzle manually**: Enter your own Sudoku puzzle
3. **Load puzzle from file**: Load a puzzle from a text file
4. **Solve current puzzle**: Solve the currently loaded puzzle
5. **Save puzzle to file**: Save the current puzzle state to a file
6. **Display current puzzle**: Show the current puzzle
7. **Clear puzzle**: Clear the current puzzle
8. **Exit**: Exit the application

## File Format

When loading or saving puzzles from/to files, the format should be:
- 9 rows of 9 digits separated by spaces
- 0 represents empty cells
- 1-9 represent filled cells

Example:
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

## Algorithm

The solver uses a backtracking algorithm:
1. Find an empty cell
2. Try placing digits 1-9 in that cell
3. Check if the placement is valid
4. Recursively try to solve the rest of the puzzle
5. If a solution is found, we're done
6. If no solution is found, backtrack and try the next number

## License

This project is licensed under the MIT License.
