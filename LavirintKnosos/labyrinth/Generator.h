#ifndef GENERATOR_H
#define GENERATOR_H

#include "Labyrinth.h"
#include <utility> // for std::pair

class Generator {
public:
    static Labyrinth* generate(int rows, int columns, int numberOfItems, std::pair<int, int> startAndEndColumn);
};

#endif // GENERATOR_H