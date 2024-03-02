#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

void printGrid(std::vector<std::vector<int>> grid) {
    std::cout << char(27) << "[2J";
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (grid[i][j] == 1) {
                // Color the cell white
                std::cout << "X ";
            } 
            else {
                // Color the cell black
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string filename;
    if (argc != 2) {
        std::cout << "No file specified, defaulting to \"Start.gol\"" << std::endl;
        filename = "Start.gol";
    }
    else {
        filename = argv[1];
    }

    std::vector<std::vector<int>> grid; // Either 0 or 1
    std::vector<std::vector<int>> newGrid; // Either 0 or 1

    // Read the file
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            row.push_back(c == '1');
        }
        grid.push_back(row);
    }

    newGrid = grid;

    printGrid(grid);
    Sleep(500);

    while (true) {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                int neighbors = 0;
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (k == 0 && l == 0) continue;
                        if (i + k < 0 || i + k >= grid.size()) continue;
                        if (j + l < 0 || j + l >= grid[i].size()) continue;
                        neighbors += grid[i + k][j + l];
                    }
                }
                if (grid[i][j] == 1) {
                    if (neighbors == 2 || neighbors == 3) {
                        newGrid[i][j] = 1;
                    } 
                    else {
                        newGrid[i][j] = 0;
                    }
                }
                else {
                    if (neighbors == 3) {
                        newGrid[i][j] = 1;
                    } 
                    else {
                        newGrid[i][j] = 0;
                    }
                }
            }
        }
        grid = newGrid;
        printGrid(grid);
        Sleep(500);
    }
}
