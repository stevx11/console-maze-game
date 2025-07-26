/*
 * Minotaur.cpp - Implementation of AI enemy minotaur
 * Random movement AI and robot interaction logic
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#include "Minotaur.h"
#include <cstdlib>

Minotaur::Minotaur(const std::pair<int, int>& startPosition) : position(startPosition) {}

// Move minotaur randomly in one of four directions
// Returns: 'V' for valid move, 'I' for invalid move (blocked by wall/bounds)
char Minotaur::move(Labyrinth& labyrinth) {
    if (!isAlive) return 'V'; // Dead minotaur doesn't move

    // Choose random direction: 0=up, 1=left, 2=down, 3=right
    int direction = std::rand() % 4;
    std::pair<int, int> newPosition = position;

    // Calculate new position based on direction
    if (direction == 0) --newPosition.first;
    else if (direction == 1) --newPosition.second;
    else if (direction == 2) ++newPosition.first;
    else if (direction == 3) ++newPosition.second;

    // Check if move is valid (within bounds and not a wall)
    if (newPosition.first >= 0 && newPosition.first < labyrinth.getRows() &&
        newPosition.second >= 0 && newPosition.second < labyrinth.getColumns() &&
        labyrinth.getCell(newPosition) != '#') {
        
        // Update labyrinth grid with new position
        labyrinth.changeGrid(position, '.');
        position = newPosition;
        labyrinth.changeGrid(newPosition, 'M');
        return 'V';
    }
    else {
        return 'I'; // Invalid move
    }
}

// Check if robot is adjacent and handle combat interaction
// Parameters: robotHasShield - robot shield protection status
//            robotHasSword - robot sword attack capability
// Returns: 0=no interaction, 1=robot caught, 2=minotaur killed
int Minotaur::checkIfRobotIsReachable(Labyrinth& labyrinth, bool robotHasShield, bool robotHasSword) {
    if (!isAlive) return 0; // Dead minotaur can't interact

    // Check all four adjacent directions for robot
    std::pair<int, int> directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < 4; i++) {
        std::pair<int, int> checkPosition = position;
        checkPosition.first += directions[i].first;
        checkPosition.second += directions[i].second;

        // If robot found adjacent, handle interaction
        if (labyrinth.getCell(checkPosition) == 'R') {
            if (robotHasShield) {
                // Robot protected by shield
                return 0;
            }
            else if (robotHasSword) {
                // Robot kills minotaur with sword
                labyrinth.changeGrid(position, '.');
                isAlive = false;
                return 2;
            }
            else {
                // Minotaur catches unprotected robot
                labyrinth.changeGrid(position, '.');
                labyrinth.changeGrid(checkPosition, 'M');
                position = checkPosition;
                return 1;
            }
        }
    }
    return 0; // No robot found adjacent
}

std::pair<int, int> Minotaur::getPosition() const {
    return position;
}

bool Minotaur::getIsAlive() const {
    return isAlive;
}