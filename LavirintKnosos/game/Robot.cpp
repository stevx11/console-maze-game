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

    if (newPosition.first >= 0 && newPosition.first < labyrinth.getRows() &&
        newPosition.second >= 0 && newPosition.second < labyrinth.getColumns() &&
        labyrinth.getCell(newPosition) != '#') {
        labyrinth.changeGrid(position, '.');
        position = newPosition;
        labyrinth.changeGrid(newPosition, 'R');
        return 'V';
    }
    else {
        std::cout << "Invalid move";
        return 'I';
    }
}

std::pair<int, int> Robot::getPosition() const {
    return position;
}