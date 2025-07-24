#include "Labyrinth.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>

Labyrinth::Labyrinth(int r, int c, int items, std::pair<int, int> startAndEndPoint) : rows(r), columns(c), numberOfItems(items), startAndEndColumn(startAndEndPoint) {
    grid = new char* [rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new char[columns];
    }

    // Initialize the grid with empty spaces
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            grid[i][j] = '.'; // Empty space
        }
    }
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

void Labyrinth::clearItems() {
    for (auto& row : items) {
        for (auto& item : row) {
            delete item;
            item = nullptr;
        }
    }
}

void Labyrinth::generateOuterWalls() {
    for (int i = 0; i < rows; ++i) {
        grid[i][0] = '#';
        grid[i][columns - 1] = '#';
    }
    for (int i = 0; i < columns; ++i) {
        grid[0][i] = '#';
        grid[rows - 1][i] = '#';
    }
}

void Labyrinth::placeRobotAndExit() {
    int robotCol = startAndEndColumn.first;
    int exitCol = startAndEndColumn.second;

    grid[1][robotCol] = 'R';   // Robot at 2nd row
    grid[0][robotCol] = 'U';   // Entrance above robot
    grid[rows - 1][exitCol] = 'I'; // Exit at last row

    // Ensure the tile *above* the exit is not a wall
    if (rows - 2 > 0) {
        grid[rows - 2][exitCol] = '.';
    }
}

void Labyrinth::generateInnerWalls() {
    // Fill the entire maze with walls then delete the ones which disrupt passability
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (grid[i][j] == '.')
                grid[i][j] = '#';
        }
    }
}

void Labyrinth::ensurePassability() {
    // Calculate minimum required walls
    int minWalls = 2 * (rows + columns);

    // Remove walls randomly until we meet the requirement
    int currentWalls = (rows - 2) * (columns - 2);
    while (currentWalls > minWalls) {
        int x = 1 + std::rand() % (rows - 2);
        int y = 1 + std::rand() % (columns - 2);

        if (grid[x][y] == '#') {
            grid[x][y] = '.';
            --currentWalls;
        }
    }

    // Ensure that the labyrinth is passable using BFS
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(columns, false));
    std::queue<std::pair<int, int>> q;
    q.push({ 1, 1 });
    visited[1][1] = true;

    while (!q.empty()) {
        std::pair<int, int> current = q.front();
        int cx = current.first;
        int cy = current.second;
        q.pop();

        for (const std::pair<int, int>& direction : std::vector<std::pair<int, int>>{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} }) {
            int dx = direction.first;
            int dy = direction.second;
            int nx = cx + dx;
            int ny = cy + dy;

            if (nx >= 1 && nx < rows - 1 && ny >= 1 && ny < columns - 1 &&
                !visited[nx][ny] && grid[nx][ny] == '.') {
                visited[nx][ny] = true;
                q.push({ nx, ny });
            }
        }
    }

    // If any reachable cell is still surrounded, make adjustments
    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < columns - 1; ++j) {
            if (!visited[i][j] && grid[i][j] == '.') {
                grid[i][j] = '#';
                ++currentWalls;
            }
        }
    }
}

void Labyrinth::display() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Labyrinth::displayWithFog(const std::pair<int, int>& robotPosition) const {
    int robotRow = robotPosition.first;
    int robotCol = robotPosition.second;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            // Check if this cell is within the 3x3 visible area around the robot
            bool isVisible = (abs(i - robotRow) <= 1 && abs(j - robotCol) <= 1);

            if (isVisible) {
                std::cout << grid[i][j] << " ";
            }
            else {
                std::cout << "  ";  // Show fog for non-visible areas
            }
        }
        std::cout << std::endl;
    }
}

void Labyrinth::placeItems() {
    int itemsPlaced = 0;
    while (itemsPlaced < numberOfItems) {
        int x = 1 + std::rand() % (rows - 2);
        int y = 1 + std::rand() % (columns - 2);

        if (grid[x][y] == '.') {
            char itemType = "FSHC"[std::rand() % 4];

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

            grid[x][y] = 'P';
            ++itemsPlaced;
        }
    }
}

const Item* Labyrinth::getItemAt(const std::pair<int, int>& position) const {
    int x = position.first;
    int y = position.second;
    if (x >= 0 && x < rows && y >= 0 && y < columns) {
        return items[x][y];
    }
    return nullptr;
}

void Labyrinth::removeItemAt(const std::pair<int, int>& position) {
    int x = position.first;
    int y = position.second;
    if (x >= 0 && x < rows && y >= 0 && y < columns && items[x][y] != nullptr) {
        delete items[x][y];
        items[x][y] = nullptr;
        grid[x][y] = '.'; // Mark as empty
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

std::pair<int, int> Labyrinth::getRandomPosition() const {
    int x = 1 + std::rand() % (rows - 2);
    int y = 1 + std::rand() % (columns - 2);
    return { x, y };
}

char Labyrinth::getCell(const std::pair<int, int>& position) const {
    int row = position.first;
    int col = position.second;

    if (row >= 0 && row < rows && col >= 0 && col < columns) {
        return grid[row][col];
    }

    // Return a special character or throw an exception
    return '#'; // wall, or any "invalid" indicator
}

int Labyrinth::getRows() const {
    return rows;
}

int Labyrinth::getColumns() const {
    return columns;
}

void Labyrinth::changeGrid(const std::pair<int, int>& cellToChange, char changeTo) {
    grid[cellToChange.first][cellToChange.second] = changeTo;
}