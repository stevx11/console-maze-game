#include "Robot.h"
#include <iostream>

Robot::Robot(const std::pair<int, int>& startPosition) : position(startPosition) {}

char Robot::move(Labyrinth& labyrinth) {
    char direction;
    std::cout << "Enter move (W/A/S/D): ";
    std::cin >> direction;

    std::pair<int, int> newPosition = position;
    if (direction == 'W' || direction == 'w') --newPosition.first;
    else if (direction == 'A' || direction == 'a') --newPosition.second;
    else if (direction == 'S' || direction == 's') ++newPosition.first;
    else if (direction == 'D' || direction == 'd') ++newPosition.second;
    else if (direction == 'Q' || direction == 'q') { return 'Q'; }

    char cellContent = labyrinth.getCell(newPosition);

    if (newPosition.first < 0 || newPosition.first >= labyrinth.getRows() ||
        newPosition.second < 0 || newPosition.second >= labyrinth.getColumns()) {
        std::cout << "Invalid move - out of bounds!\n";
        return 'I';
    }

    // Check if it's a wall
    if (cellContent == '#') {
        // If robot has hammer, can break walls
        if (powerUps.hasHammer()) {
            std::cout << "Using hammer to break wall!\n";
            labyrinth.changeGrid(position, '.');
            position = newPosition;
            labyrinth.changeGrid(newPosition, 'R');
            return 'V';
        }
        else {
            std::cout << "Invalid move - wall in the way!\n";
            return 'I';
        }
    }
    if (cellContent == '.' || cellContent == 'P' || cellContent == 'I') {
        labyrinth.changeGrid(position, '.');
        position = newPosition;
        labyrinth.changeGrid(newPosition, 'R');
        return 'V';
    }

    std::cout << "Invalid move!\n";
    return 'I';
}

std::pair<int, int> Robot::getPosition() const {
    return position;
}

void Robot::collectItem(const Item* item) {
    if (!item) return;

    std::string itemType = item->getType();

    if (itemType == "SWORD") {
        powerUps.activateSword();
        std::cout << "Sword activated! You can kill the Minotaur for 3 turns.\n";
    }
    else if (itemType == "SHIELD") {
        powerUps.activateShield();
        std::cout << "Shield activated! You are protected from the Minotaur for 3 turns.\n";
    }
    else if (itemType == "HAMMER") {
        powerUps.activateHammer();
        std::cout << "Hammer activated! You can break walls for 3 turns.\n";
    }
    else if (itemType == "FOG") {
        powerUps.activateFog();
        std::cout << "Fog activated! Visibility reduced to 3x3 for 3 turns.\n";
    }
}