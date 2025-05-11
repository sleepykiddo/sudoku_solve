cmake_minimum_required(VERSION 3.10)
project(SudokuSolver VERSION 1.0 LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set Clang as the compiler
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/SudokuSolver.cpp
)

# Create executable
add_executable(sudoku_solver ${SOURCES})

# Install target
install(TARGETS sudoku_solver DESTINATION bin)

# Testing configuration
option(BUILD_TESTS "Build the tests" ON)
if(BUILD_TESTS)
    # Use FetchContent to download and configure GoogleTest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)
    
    # Enable testing
    enable_testing()
    
    # Add test executable
    add_executable(sudoku_tests tests/test_sudoku.cpp src/SudokuSolver.cpp)
    target_link_libraries(sudoku_tests gtest gtest_main)
    
    # Add test to CTest
    add_test(NAME SudokuTests COMMAND sudoku_tests)
endif()

# Installation rules
install(TARGETS sudoku_solver DESTINATION bin)
install(FILES include/SudokuSolver.hpp DESTINATION include)
