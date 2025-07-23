#ifndef MINOTAUR_H
#define MINOTAUR_H

#include <utility>
#include "../labyrinth/Labyrinth.h"

class Minotaur {
private:
    std::pair<int, int> position;

public:
    Minotaur(const std::pair<int, int>& startPosition);
    char move(Labyrinth& labyrinth);
    int checkIfRobotIsReachable(Labyrinth& labyrinth);
    std::pair<int, int> getPosition() const;
};

#endif // MINOTAUR_H