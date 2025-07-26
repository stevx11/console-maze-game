/*
 * Labyrinth.cpp - Implementation of main labyrinth grid system
 * Grid management, generation algorithms, and display functionality
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#include "Labyrinth.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

Labyrinth::Labyrinth(int r, int c, int items, std::pair<int, int> startAndEndPoint)
    : rows(r), columns(c), numberOfItems(items), startAndEndColumn(startAndEndPoint) {

    // Allocate 2D character grid
    grid = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[columns];
    }

    // Initialize grid with empty spaces
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            grid[i][j] = '.';
        }
    }

    // Initialize item grid
    this->items.resize(rows, std::vector<Item*>(columns, nullptr));
    std::srand(std::time(nullptr));
}

Labyrinth::~Labyrinth() {
    clearItems();
    for (int i = 0; i < rows; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

// Clean up all dynamically allocated items
void Labyrinth::clearItems() {
    for (auto& row : items) {
        for (auto& item : row) {
            delete item;
            item = nullptr;
        }
    }
}

// Generate perimeter walls around the entire labyrinth
void Labyrinth::generateOuterWalls() {
    // Create vertical walls (left and right edges)
    for (int i = 0; i < rows; ++i) {
        grid[i][0] = '#';
        grid[i][columns - 1] = '#';
    }
    // Create horizontal walls (top and bottom edges)
    for (int i = 0; i < columns; ++i) {
        grid[0][i] = '#';
        grid[rows - 1][i] = '#';
    }
}

// Place robot at entry and exit marker at specified positions
void Labyrinth::placeRobotAndExit() {
    int robotCol = startAndEndColumn.first;
    int exitCol = startAndEndColumn.second;

    grid[1][robotCol] = 'R';        // Robot at second row
    grid[0][robotCol] = 'U';        // Entrance marker above robot
    grid[rows - 1][exitCol] = 'I';  // Exit at bottom row

    // Ensure path to exit is clear
    if (rows - 2 > 0) {
        grid[rows - 2][exitCol] = '.';
    }
}

// Generate internal wall structure using grid based algorithm
// Creates maze structure with random connectivity
void Labyrinth::generateInnerWalls() {
    int innerWallCount = 0;

    // Place walls at regular grid intervals
    for (int i = 2; i < rows - 2; i += 2) {
        for (int j = 2; j < columns - 2; j += 2) {
            // 5% chance to skip wall for variation
            if (rand() % 100 < 5) continue;

            // Avoid overwriting special positions
            if ((i == 1 && j == startAndEndColumn.first) ||
                (i == rows - 2 && j == startAndEndColumn.second)) continue;

            grid[i][j] = '#';
            innerWallCount++;

            // Add random connecting wall segment
            int dir = rand() % 4;
            int dx = 0, dy = 0;
            if (dir == 0) dx = -1;
            else if (dir == 1) dx = 1;
            else if (dir == 2) dy = -1;
            else dy = 1;

            int ni = i + dx;
            int nj = j + dy;

            // Place connecting wall if within bounds
            if (ni >= 1 && ni < rows - 1 && nj >= 1 && nj < columns - 1) {
                grid[ni][nj] = '#';
                innerWallCount++;
            }
        }
    }

    // Ensure minimum wall density for maze complexity
    if (innerWallCount < (2 * (rows + columns))) {
        generateInnerWalls();
    }
}

// Display full labyrinth to console
void Labyrinth::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Display labyrinth with fog effect (3x3 visibility around robot)
void Labyrinth::displayWithFog(const std::pair<int, int>& robotPosition) const {
    int robotRow = robotPosition.first;
    int robotCol = robotPosition.second;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // Check if cell is within visible range
            bool isVisible = (abs(i - robotRow) <= 1 && abs(j - robotCol) <= 1);

            if (isVisible) {
                std::cout << grid[i][j] << " ";
            }
            else {
                std::cout << "  ";  // Fog shows non visible areas as a empty spot
            }
        }
        std::cout << std::endl;
    }
}

// Randomly place items throughout the labyrinth
void Labyrinth::placeItems() {
    int itemsPlaced = 0;

    while (itemsPlaced < numberOfItems) {
        // Generate random position (avoid borders)
        int x = 1 + std::rand() % (rows - 2);
        int y = 1 + std::rand() % (columns - 2);

        // Only place on empty cells
        if (grid[x][y] == '.') {
            // Random item type: F=Fog, S=Sword, H=Hammer, C=Shield
            char itemType = "FSHC"[std::rand() % 4];

            // Create appropriate item object
            switch (itemType) {
            case 'F':
                items[x][y] = new Fog(std::make_pair(x, y));
                break;
            case 'S':
                items[x][y] = new Sword(std::make_pair(x, y));
                break;
            case 'H':
                items[x][y] = new Hammer(std::make_pair(x, y));
                break;
            case 'C':
                items[x][y] = new Shield(std::make_pair(x, y));
                break;
            }

            grid[x][y] = 'P';  // Mark position with item symbol
            ++itemsPlaced;
        }
    }
}

// Get item at specified position (null if none)
const Item* Labyrinth::getItemAt(const std::pair<int, int>& position) const {
    int x = position.first;
    int y = position.second;
    if (x >= 0 && x < rows && y >= 0 && y < columns) {
        return items[x][y];
    }
    return nullptr;
}

// Remove item at specified position and mark cell as empty
void Labyrinth::removeItemAt(const std::pair<int, int>& position) {
    int x = position.first;
    int y = position.second;
    if (x >= 0 && x < rows && y >= 0 && y < columns && items[x][y] != nullptr) {
        delete items[x][y];
        items[x][y] = nullptr;
        grid[x][y] = '.';
    }
}

std::pair<int, int> Labyrinth::getExit() const {
    std::pair<int, int> LabyrinthExit = { getRows() - 1, startAndEndColumn.second };
    return LabyrinthExit;
}

std::pair<int, int> Labyrinth::getEntry() const {
    std::pair<int, int> LabyrinthEntry = { 0, startAndEndColumn.first };
    return LabyrinthEntry;
}

// Generate random valid position within labyrinth bounds
std::pair<int, int> Labyrinth::getRandomPosition() const {
    int x = 1 + std::rand() % (rows - 2);
    int y = 1 + std::rand() % (columns - 2);
    return { x, y };
}

// Get character at specified position (returns '#' for out of bounds)
char Labyrinth::getCell(const std::pair<int, int>& position) const {
    int row = position.first;
    int col = position.second;

    if (row >= 0 && row < rows && col >= 0 && col < columns) {
        return grid[row][col];
    }

    return '#'; // Return wall character for invalid positions
}

int Labyrinth::getRows() const {
    return rows;
}

int Labyrinth::getColumns() const {
    return columns;
}

// Update grid cell at specified position
void Labyrinth::changeGrid(const std::pair<int, int>& cellToChange, char changeTo) {
    grid[cellToChange.first][cellToChange.second] = changeTo;
}