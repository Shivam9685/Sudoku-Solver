#include <iostream>
#include <vector>

const int N = 9;

class Sudoku {
public:
    Sudoku(const std::vector<std::vector<int>>& puzzle);
    void solve();
    void display();

private:
    bool isSafe(int row, int col, int num);
    bool findUnassignedLocation(int& row, int& col);
    bool solveSudoku();
    std::vector<std::vector<int>> grid;
};

Sudoku::Sudoku(const std::vector<std::vector<int>>& puzzle) {
    grid = puzzle;
}

void Sudoku::display() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Sudoku::isSafe(int row, int col, int num) {
    // Check if 'num' is not present in the current row and column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not present in the 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::findUnassignedLocation(int& row, int& col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool Sudoku::solveSudoku() {
    int row, col;
    if (!findUnassignedLocation(row, col)) {
        return true; // Puzzle is solved
    }

    for (int num = 1; num <= N; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku()) {
                return true;
            }

            grid[row][col] = 0; // Backtrack and try the next number
        }
    }

    return false; // No solution found
}

void Sudoku::solve() {
    if (solveSudoku()) {
        std::cout << "Sudoku puzzle solved successfully:" << std::endl;
        display();
    } else {
        std::cout << "No solution exists for the given Sudoku puzzle." << std::endl;
    }
}

int main() {
    // Replace this example with your unsolved Sudoku puzzle (use 0 for blank cells)
    std::vector<std::vector<int>> puzzle = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    Sudoku sudoku(puzzle);
    sudoku.solve();

    return 0;
}
