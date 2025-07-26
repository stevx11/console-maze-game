/*
 * Generator.cpp - Implementation of labyrinth generation
 * Timed generation process with performance logging
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#include "Generator.h"
#include "../utils/Timer.h"
#include "../utils/Utils.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

 // Generate complete labyrinth with timing and performance logging
 // Parameters: rows, columns - labyrinth dimensions (minimum 15x15)
 //            numberOfItems - items to place (minimum 3)
 //            startAndEndColumn - entry and exit column positions
 // Returns: pointer to fully generated labyrinth
Labyrinth* Generator::generate(int rows, int columns, int numberOfItems, std::pair<int, int> startAndEndColumn) {
    std::srand(std::time(nullptr));  // Initialize random seed, ensures labyrinth will be different every time

    // Start performance timing
    Timer generationTimer;
    generationTimer.start();

    // Create empty labyrinth
    Labyrinth* lab = new Labyrinth(rows, columns, numberOfItems, startAndEndColumn);

    // Execute generation steps in sequence
    lab->generateOuterWalls();    // Create perimeter
    lab->generateInnerWalls();    // Create maze structure
    lab->placeItems();            // Add collectible items
    lab->placeRobotAndExit();     // Position robot, entry and exit

    // Stop timing and collect performance data
    generationTimer.stop();
    double generationTimeMs = generationTimer.getElapsedMilliseconds();

    // Create detailed performance report
    std::string report = Utils::formatGenerationReport(
        rows, columns, numberOfItems, generationTimeMs);

    // Log performance data to file
    std::string logFilename = "labyrinth_generation_log.txt";
    Utils::appendToFile(logFilename, report);

    return lab;
}