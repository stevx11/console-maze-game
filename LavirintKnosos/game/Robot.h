/*
 * Robot.h - Player controlled robot class
 * Handles movement, item collection and powerup management
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <utility>
#include "../labyrinth/Labyrinth.h"
#include "../items/Items.h"


class Robot {
private:
    std::pair<int, int> position;    // Current robot position
    PowerUpManager powerUps;         // Active power-up manager

public:
    // Constructor, places robot at starting position
    Robot(const std::pair<int, int>& startPosition);

    // Process player movement input - returns 'V' valid, 'I' invalid, 'Q' quit
    char move(Labyrinth& labyrinth);

    // Get current robot position
    std::pair<int, int> getPosition() const;

    // Get power-up manager reference
    PowerUpManager& getPowerUps() { return powerUps; }
    const PowerUpManager& getPowerUps() const { return powerUps; }

    // Collect and activate an item effect
    void collectItem(const Item* item);

    // Decrement all active powerup turn counters
    void decrementPowerUpTurns() { powerUps.decrementTurns(); }
};

#endif // ROBOT_H