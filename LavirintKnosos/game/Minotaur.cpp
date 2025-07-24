#include "Minotaur.h"
#include <cstdlib>

Minotaur::Minotaur(const std::pair<int, int>& startPosition) : position(startPosition) {}

char Minotaur::move(Labyrinth& labyrinth) {
    if (!isAlive) return 'V'; // Dead minotaur doesn't move

    int direction = std::rand() % 4; // 0: up, 1: left, 2: down, 3: right
    std::pair<int, int> newPosition = position;

    if (direction == 0) --newPosition.first;
    else if (direction == 1) --newPosition.second;
    else if (direction == 2) ++newPosition.first;
    else if (direction == 3) ++newPosition.second;

    if (newPosition.first >= 0 && newPosition.first < labyrinth.getRows() &&
        newPosition.second >= 0 && newPosition.second < labyrinth.getColumns() &&
        labyrinth.getCell(newPosition) != '#') {
        labyrinth.changeGrid(position, '.');
        position = newPosition;
        labyrinth.changeGrid(newPosition, 'M');
        return 'V';
    }
    else {
        return 'I';
    }
}

int Minotaur::checkIfRobotIsReachable(Labyrinth& labyrinth, bool robotHasShield, bool robotHasSword) {
    if (!isAlive) return 0; // Dead minotaur can't catch robot

    std::pair<int, int> directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    for (int i = 0; i < 4; i++) {
        std::pair<int, int> checkPosition = position;
        checkPosition.first += directions[i].first;
        checkPosition.second += directions[i].second;

        if (labyrinth.getCell(checkPosition) == 'R') {
            if (robotHasShield) {
                // Robot is protected by shield
                return 0;
            }
            else if (robotHasSword) {
                // Robot kills the minotaur
                labyrinth.changeGrid(position, '.');
                isAlive = false;
                return 2; // Special return code for minotaur death
            }
            else {
                // Minotaur catches robot
                labyrinth.changeGrid(position, '.');
                labyrinth.changeGrid(checkPosition, 'M');
                position = checkPosition;
                return 1;
            }
        }
    }
    return 0;
}

std::pair<int, int> Minotaur::getPosition() const {
    return position;
}

bool Minotaur::getIsAlive() const {
    return isAlive;
}