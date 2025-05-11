#include "../include/SudokuSolver.hpp"
#include <iostream>
#include <limits> // For std::numeric_limits
#include <string>

void printMenu() {
    std::cout << "\n===== SUDOKU SOLVER =====\n";
    std::cout << "1. Load sample puzzle\n";
    std::cout << "2. Enter puzzle manually\n";
    std::cout << "3. Load puzzle from file\n";
    std::cout << "4. Solve current puzzle\n";
    std::cout << "5. Save puzzle to file\n";
    std::cout << "6. Display current puzzle\n";
    std::cout << "7. Clear puzzle\n";
    std::cout << "8. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    SudokuSolver solver;
    bool running = true;
    int choice;
    std::string filename;

    std::cout << "Welcome to the Sudoku Solver!\n";

    while (running) {
        printMenu();
        std::cin >> choice;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1: // Load sample puzzle
            solver.setSamplePuzzle();
            std::cout << "Sample puzzle loaded.\n";
            solver.printGrid();
            break;

        case 2: // Enter puzzle manually
            solver.setGridFromUserInput();
            if (!solver.isValidPuzzle()) {
                std::cout << "Warning: The entered puzzle may not be valid.\n";
            }
            std::cout << "Puzzle entered successfully.\n";
            solver.printGrid();
            break;

        case 3: // Load puzzle from file
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            if (solver.loadFromFile(filename)) {
                std::cout << "Puzzle loaded from " << filename << ".\n";
                solver.printGrid();
                if (!solver.isValidPuzzle()) {
                    std::cout
                        << "Warning: The loaded puzzle may not be valid.\n";
                }
            } else {
                std::cout << "Failed to load puzzle from " << filename << ".\n";
            }
            break;

        case 4: // Solve current puzzle
            std::cout << "Solving puzzle...\n";
            if (solver.solve()) {
                std::cout << "Puzzle solved!\n";
                solver.printGrid();
            } else {
                std::cout << "No solution exists for this puzzle.\n";
            }
            break;

        case 5: // Save puzzle to file
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            if (solver.saveToFile(filename)) {
                std::cout << "Puzzle saved to " << filename << ".\n";
            } else {
                std::cout << "Failed to save puzzle to " << filename << ".\n";
            }
            break;

        case 6: // Display current puzzle
            std::cout << "Current puzzle:\n";
            solver.printGrid();
            break;

        case 7: // Clear puzzle
            solver.clear();
            std::cout << "Puzzle cleared.\n";
            break;

        case 8: // Exit
            std::cout << "Exiting program. Goodbye!\n";
            running = false;
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}