#include "Generator.h"
#include "../utils/Timer.h"
#include "../utils/Utils.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Labyrinth* Generator::generate(int rows, int columns, int numberOfItems, std::pair<int, int> startAndEndColumn) {
    std::srand(std::time(nullptr));  // Ensure randomness

    // Start timing the generation process
    Timer generationTimer;
    generationTimer.start();

    Labyrinth* lab = new Labyrinth(rows, columns, numberOfItems, startAndEndColumn);

    // Step-by-step generation with individual timing (optional for debugging)
    lab->generateOuterWalls();
    lab->generateInnerWalls();
    lab->placeItems();
    lab->placeRobotAndExit();

    // Stop timing
    generationTimer.stop();

    // Get generation time
    double generationTimeMs = generationTimer.getElapsedMilliseconds();

    // Create detailed report
    std::string report = Utils::formatGenerationReport(
        rows, columns, numberOfItems, generationTimeMs);

    // Write to detailed log file
    std::string logFilename = "labyrinth_generation_log.txt";
    Utils::appendToFile(logFilename, report);

    // Console output
    std::cout << "Labyrinth generated successfully!\n";
    std::cout << "Generation time: " << generationTimer.getFormattedTime() << "\n";
    std::cout << "Performance data written to: " << logFilename;

    return lab;
}