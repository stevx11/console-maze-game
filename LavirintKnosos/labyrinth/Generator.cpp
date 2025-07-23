#include "Generator.h"
#include <cstdlib>
#include <ctime>

Labyrinth* Generator::generate(int rows, int columns, int numberOfItems, std::pair<int,int> startAndEndColumn) {
    std::srand(std::time(nullptr));  // Ensure randomness

    Labyrinth* lab = new Labyrinth(rows, columns, numberOfItems,startAndEndColumn);

    // Step-by-step generation
    lab->generateOuterWalls();
    lab->generateInnerWalls();
    lab->ensurePassability();
    lab->placeItems();
    lab->placeRobotAndExit();
    return lab;
}