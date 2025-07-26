/*
 * Minotaur.h - Enemy minotaur class
 * Computer controlled enemy that hunts the robot
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef MINOTAUR_H
#define MINOTAUR_H

#include <utility>
#include "../labyrinth/Labyrinth.h"

class Minotaur {
private:
    std::pair<int, int> position;    // Current minotaur position
    bool isAlive;                    // Whether minotaur is alive

public:
    // Constructor, places minotaur at starting position
    Minotaur(const std::pair<int, int>& startPosition);

    // Move randomly - returns 'V' valid move, 'I' invalid move
    char move(Labyrinth& labyrinth);

    // Check if robot is adjacent and handle interaction
    // Returns: 0=no interaction, 1=robot caught, 2=minotaur killed
    int checkIfRobotIsReachable(Labyrinth& labyrinth, bool robotHasShield, bool robotHasSword);

    // Get current minotaur position
    std::pair<int, int> getPosition() const;

    // Check if minotaur is still alive
    bool getIsAlive() const;
};

#endif // MINOTAUR_H