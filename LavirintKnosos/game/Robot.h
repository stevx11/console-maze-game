#ifndef ROBOT_H
#define ROBOT_H

#include <utility>
#include "../labyrinth/Labyrinth.h"
#include "../items/Items.h"

class Robot {
private:
    std::pair<int, int> position;
    PowerUpManager powerUps;

public:
    Robot(const std::pair<int, int>& startPosition);
    char move(Labyrinth& labyrinth);
    std::pair<int, int> getPosition() const;
    PowerUpManager& getPowerUps() { return powerUps; }
    const PowerUpManager& getPowerUps() const { return powerUps; }
    void collectItem(const Item* item);
    void decrementPowerUpTurns() { powerUps.decrementTurns(); }
};

#endif // ROBOT_H