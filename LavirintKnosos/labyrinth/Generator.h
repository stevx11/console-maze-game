/*
 * Generator.h - Labyrinth generation utility
 * Static factory class for creating complete labyrinths
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include "Labyrinth.h"
#include <utility>

class Generator {
public:
    // Generate complete labyrinth with timing and logging
    // Returns: pointer to generated labyrinth
    // Parameters: dimensions, item count, entry/exit columns
    static Labyrinth* generate(int rows, int columns, int numberOfItems,
        std::pair<int, int> startAndEndColumn);
};

#endif // GENERATOR_H