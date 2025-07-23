#include "Minotaur.h"
#include <cstdlib>

Minotaur::Minotaur(const std::pair<int, int>& startPosition) : position(startPosition) {}

char Minotaur::move(Labyrinth& labyrinth) {
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

int Minotaur::checkIfRobotIsReachable(Labyrinth& labyrinth) {
    std::pair<int, int> positionUp = position;
    positionUp.first = --positionUp.first;
    if (labyrinth.getCell(positionUp) == 'R') {
        labyrinth.changeGrid(position, '.');
        labyrinth.changeGrid(positionUp, 'M');
        return 1;

    }
    std::pair<int, int> positionDown = position;
    positionDown.first = ++positionDown.first;
    if (labyrinth.getCell(positionDown) == 'R') {
        labyrinth.changeGrid(position, '.');
        labyrinth.changeGrid(positionDown, 'M');
        return 1;

    }
    std::pair<int, int> positionLeft = position;
    positionLeft.second = --positionLeft.second;
    if (labyrinth.getCell(positionLeft) == 'R') {
        labyrinth.changeGrid(position, '.');
        labyrinth.changeGrid(positionLeft, 'M');
        return 1;

    }
    std::pair<int, int> positionRight = position;
    positionRight.first = ++positionRight.second;
    if (labyrinth.getCell(positionRight) == 'R') {
        labyrinth.changeGrid(position, '.');
        labyrinth.changeGrid(positionRight, 'M');
        return 1;

    }
    return 0;
}

std::pair<int, int> Minotaur::getPosition() const {
    return position;
}