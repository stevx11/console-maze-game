/*
 * main.cpp - Program entry point and command line processing
 * Handles arguments, generates labyrinth, and starts game
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#include <iostream>
#include "./labyrinth/Labyrinth.h"
#include "./game/Robot.h"
#include "./game/Minotaur.h"
#include "./items/Items.h"
#include "./labyrinth/Generator.h"
#include "./game/Game.h"
#include "./utils/Utils.h"

 // Main program entry point
 // Arguments: <rows> <columns> <number_of_items>
 // Returns: 0 on success, 1 on error
int main(int argc, char* argv[]) {
    // Validate command line arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <rows> <columns> <number_of_items>\n";
        return 1;
    }

    // Parse labyrinth parameters
    int rows = std::stoi(argv[1]);
    int columns = std::stoi(argv[2]);
    int numberOfItems = std::stoi(argv[3]);

    // Validate parameter ranges
    if (rows < 15 || columns < 15 || numberOfItems < 3) {
        std::cerr << "Rows and columns must be >= 15, and the number of items must be >= 3.\n";
        return 1;
    }

    // Generate random entry and exit points
    int startPoint = 1 + std::rand() % (columns - 2);
    int endPoint = 1 + std::rand() % (columns - 2);

    std::cout << "Generating labyrinth (" << rows << "x" << columns << ") with " << numberOfItems << " items...\n";

    // Generate the labyrinth with performance timing
    Labyrinth* labyrinth = Generator::generate(rows, columns, numberOfItems, { startPoint, endPoint });

    // Start and run the game
    Game game(labyrinth);
    game.run();

    return 0;
}