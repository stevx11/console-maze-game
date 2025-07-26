/*
 * Labyrinth.h - Main labyrinth structure and management
 * Handles grid, items, display, and navigation
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "../items/Items.h"
#include <vector>
#include <string>
#include <memory>

 /*
  * Main labyrinth class that manages the game grid
  * Handles walls, items, display, and entity positioning
  */
class Labyrinth {
private:
    int rows;                                    // Number of grid rows
    int columns;                                 // Number of grid columns
    int numberOfItems;                           // Total items to place
    std::pair<int, int> startAndEndColumn;      // Entry and exit column positions
    char** grid;                                // 2D character grid
    std::vector<std::vector<Item*>> items;      // 2D item pointer grid

public:
    // Constructor, initializes empty labyrinth
    Labyrinth(int r, int c, int items, std::pair<int, int> startAndEndColumn);

    // Destructor,  qcleans up grid and items
    ~Labyrinth();

    // Generation methods
    void generateOuterWalls();     // Create perimeter walls
    void placeRobotAndExit();     // Place entry, exit, and robot
    void generateInnerWalls();    // Create internal maze structure
    void placeItems();            // Randomly place items
    void clearItems();            // Clean up all items

    // Display methods
    void display() const;         // Show full labyrinth
    void displayWithFog(const std::pair<int, int>& robotPosition) const; // Show 3x3 view

    // Position methods
    std::pair<int, int> getEntry() const;          // Get entry coordinates
    std::pair<int, int> getExit() const;           // Get exit coordinates
    std::pair<int, int> getRandomPosition() const; // Get random valid position

    // Grid access methods
    char getCell(const std::pair<int, int>& position) const;        // Get cell content
    int getRows() const;                                            // Get row count
    int getColumns() const;                                         // Get column count
    void changeGrid(const std::pair<int, int>& position, char changeTo); // Update cell

    // Item management methods
    const Item* getItemAt(const std::pair<int, int>& position) const; // Get item at position
    void removeItemAt(const std::pair<int, int>& position);           // Remove item
};

#endif // LABYRINTH_H