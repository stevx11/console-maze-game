#ifndef ROBOT_H
#define ROBOT_H

#include <utility>
#include "../labyrinth/Labyrinth.h"

class Robot {
private:
    std::pair<int, int> position;

public:
    Robot(const std::pair<int, int>& startPosition);
    char move(Labyrinth& labyrinth);
    std::pair<int, int> getPosition() const;
};

#endif // ROBOT_H