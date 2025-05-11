#ifndef SUDOKU_SOLVER_HPP
#define SUDOKU_SOLVER_HPP

#include <string>

class SudokuSolver {
  private:
    static const int GRID_SIZE = 9;
    static const int BOX_SIZE = 3;
    int grid[GRID_SIZE][GRID_SIZE];

    // Helper methods for solving
    bool isSafe(int row, int col, int num) const;
    bool findEmptyCell(int &row, int &col) const;
    bool solveSudokuUtil();

  public:
    // Constructor and initialization
    SudokuSolver();

    // Core functionality
    void clear();
    void setCell(int row, int col, int value);
    int getCell(int row, int col) const;
    bool loadFromFile(const std::string &filename);
    bool saveToFile(const std::string &filename) const;
    bool solve();

    // Display methods
    void printGrid() const;
    std::string toString() const;

    // Grid manipulation
    void setSamplePuzzle();
    void setGrid(const int inputGrid[GRID_SIZE][GRID_SIZE]);
    void setGridFromUserInput();
    bool isValidPuzzle() const;
};

#endif // SUDOKU_SOLVER_HPP