// Main program file: main.cpp
// Description: Runs the game flow, processes command line arguments, and connects modules.
// Author: Your Name
// Last modification date: XX.YY.202Z

#include <iostream>
#include "./labyrinth/Labyrinth.h"
#include "./game/Robot.h"
#include "./game/Minotaur.h"
#include "./items/Items.h"
#include "./labyrinth/Generator.h"
#include "./game/Game.h"
#include "./utils/Utils.h"

int main(int argc, char* argv[]) {
    // Check the validity of command line arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <rows> <columns> <number_of_items>\n";
        return 1;
    }

    // Read labyrinth dimensions and number of items
    int rows = std::stoi(argv[1]);
    int columns = std::stoi(argv[2]);
    int numberOfItems = std::stoi(argv[3]);

    // Validate arguments
    if (rows < 15 || columns < 15 || numberOfItems < 3) {
        std::cerr << "Rows and columns must be >= 15, and the number of items must be >= 3.\n";
        return 1;
    }

    int startPoint = 1 + std::rand() % (columns - 2);
    int endPoint = 1 + std::rand() % (columns - 2);

    std::cout << "Generating labyrinth (" << rows << "x" << columns << ") with " << numberOfItems << " items...\n";

    // Generate the labyrinth (timing is handled inside Generator::generate)
    Labyrinth* labyrinth = Generator::generate(rows, columns, numberOfItems, { startPoint, endPoint });

    // Start the game
    Game game(labyrinth);
    game.run();

    return 0;
}