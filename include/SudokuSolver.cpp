#include "../include/SudokuSolver.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

SudokuSolver::SudokuSolver() { clear(); }

void SudokuSolver::clear() {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

void SudokuSolver::setCell(int row, int col, int value) {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE &&
        value >= 0 && value <= 9) {
        grid[row][col] = value;
    }
}

int SudokuSolver::getCell(int row, int col) const {
    if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
        return grid[row][col];
    }
    return -1; // Invalid cell
}

bool SudokuSolver::isSafe(int row, int col, int num) const {
    // Check row
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[row][x] == num) {
            return false;
        }
    }

    // Check column
    for (int x = 0; x < GRID_SIZE; x++) {
        if (grid[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 box
    int startRow = row - row % BOX_SIZE;
    int startCol = col - col % BOX_SIZE;

    for (int i = 0; i < BOX_SIZE; i++) {
        for (int j = 0; j < BOX_SIZE; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuSolver::findEmptyCell(int &row, int &col) const {
    for (row = 0; row < GRID_SIZE; row++) {
        for (col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool SudokuSolver::solveSudokuUtil() {
    int row, col;

    // If no empty cell is found, puzzle is solved
    if (!findEmptyCell(row, col)) {
        return true;
    }

    // Try digits 1-9 for the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            // Try this number
            grid[row][col] = num;

            // Recursively try to solve the rest
            if (solveSudokuUtil()) {
                return true;
            }

            // If placing num doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    // Trigger backtracking
    return false;
}

bool SudokuSolver::solve() { return solveSudokuUtil(); }

void SudokuSolver::printGrid() const {
    std::cout << "+-------+-------+-------+" << std::endl;
    for (int i = 0; i < GRID_SIZE; i++) {
        std::cout << "| ";
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 0) {
                std::cout << ". ";
            } else {
                std::cout << grid[i][j] << " ";
            }

            if ((j + 1) % BOX_SIZE == 0) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;

        if ((i + 1) % BOX_SIZE == 0) {
            std::cout << "+-------+-------+-------+" << std::endl;
        }
    }
}

std::string SudokuSolver::toString() const {
    std::stringstream ss;
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            ss << grid[i][j];
            if (j < GRID_SIZE - 1) {
                ss << " ";
            }
        }
        if (i < GRID_SIZE - 1) {
            ss << std::endl;
        }
    }
    return ss.str();
}

void SudokuSolver::setSamplePuzzle() {
    int samplePuzzle[GRID_SIZE][GRID_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    setGrid(samplePuzzle);
}

void SudokuSolver::setGrid(const int inputGrid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = inputGrid[i][j];
        }
    }
}

void SudokuSolver::setGridFromUserInput() {
    std::cout << "Enter the Sudoku puzzle (9x9 grid):" << std::endl;
    std::cout << "Use 0 for empty cells and 1-9 for filled cells." << std::endl;

    for (int i = 0; i < GRID_SIZE; i++) {
        std::cout << "Enter row " << (i + 1)
                  << " (9 numbers separated by spaces): ";
        for (int j = 0; j < GRID_SIZE; j++) {
            int value;
            std::cin >> value;

            // Validate input
            while (value < 0 || value > 9) {
                std::cout
                    << "Invalid input! Please enter a number between 0-9: ";
                std::cin >> value;
            }

            grid[i][j] = value;
        }
    }
}

bool SudokuSolver::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    clear();
    int tempGrid[GRID_SIZE][GRID_SIZE] = {
        0}; // Temporary grid to avoid partial loading
    std::string line;
    int row = 0;

    // Read file line by line
    while (std::getline(file, line) && row < GRID_SIZE) {
        std::istringstream iss(line);
        int col = 0;
        int value;

        // Process each number in the line
        while (iss >> value && col < GRID_SIZE) {
            if (value < 0 || value > 9) {
                std::cerr << "Error: Invalid value " << value
                          << " at position [" << row << "," << col
                          << "] in file " << filename << std::endl;
                return false;
            }
            tempGrid[row][col] = value;
            col++;
        }

        // Check if we got enough values for this row
        if (col < GRID_SIZE) {
            std::cerr << "Error: Not enough values in row " << row
                      << " in file " << filename << std::endl;
            return false;
        }

        // Check if there are extra values in the line
        if (iss >> value) {
            std::cerr << "Error: Too many values in row " << row << " in file "
                      << filename << std::endl;
            return false;
        }

        row++;
    }

    // Check if we got enough rows
    if (row < GRID_SIZE) {
        std::cerr << "Error: Not enough rows in file " << filename << std::endl;
        return false;
    }

    // Only if all data is valid, copy to the actual grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            grid[i][j] = tempGrid[i][j];
        }
    }

    return true;
}

bool SudokuSolver::saveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file) {
        return false;
    }

    file << toString();
    return !file.fail();
}

bool SudokuSolver::isValidPuzzle() const {
    // Check each cell for validity without modifying the grid
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            int num = grid[i][j];
            if (num != 0) {
                // Check if this number appears elsewhere in the row
                for (int col = 0; col < GRID_SIZE; col++) {
                    if (col != j && grid[i][col] == num) {
                        return false;
                    }
                }

                // Check if this number appears elsewhere in the column
                for (int row = 0; row < GRID_SIZE; row++) {
                    if (row != i && grid[row][j] == num) {
                        return false;
                    }
                }

                // Check if this number appears elsewhere in the 3x3 box
                int boxStartRow = i - i % BOX_SIZE;
                int boxStartCol = j - j % BOX_SIZE;
                for (int row = boxStartRow; row < boxStartRow + BOX_SIZE;
                     row++) {
                    for (int col = boxStartCol; col < boxStartCol + BOX_SIZE;
                         col++) {
                        if ((row != i || col != j) && grid[row][col] == num) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}