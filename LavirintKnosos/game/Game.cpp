#include "Game.h"
#include <iostream>

Game::Game(Labyrinth* lab)
    : labyrinth(lab), gameOver(false)
{
    LabyrinthExit = labyrinth->getExit();
    robot = new Robot({ 1,labyrinth->getEntry().second });
    std::pair<int, int> minotaurStartPosition = labyrinth->getRandomPosition();
    minotaur = new Minotaur(minotaurStartPosition);
    labyrinth->changeGrid(minotaurStartPosition, 'M');
}

Game::~Game() {
    delete robot;
    delete minotaur;
    delete labyrinth;
}

void Game::run() {
    std::cout << "Welcome to the Labyrinth of Knossos!\n";
    std::cout << "Controls: W/A/S/D to move, Q to quit\n";
    std::cout << "Find items (P) to gain powers, reach the exit (I) to win!\n\n";

    while (!gameOver) {
        display();

        // Display active power-ups
        std::string activeEffects = robot->getPowerUps().getActiveEffects();
        if (!activeEffects.empty()) {
            std::cout << "Active effects: " << activeEffects << "\n";
        }

        // Check if robot is on an item
        const Item* item = labyrinth->getItemAt(robot->getPosition());
        if (item) {
            std::cout << "Robot found an item: " << item->getEffect() << "\n";
            robot->collectItem(item);
            labyrinth->removeItemAt(robot->getPosition());
        }

        // Robot move
        char robotMoveValid = robot->move(*labyrinth);

        if (robotMoveValid == 'Q') {
            std::cout << "You chose to quit the game\n";
            gameOver = true;
            continue;
        }
        else if (robotMoveValid == 'I') {
            continue; // Invalid move, try again
        }

        // Check if robot reached exit
        if (robot->getPosition() == LabyrinthExit) {
            std::cout << "Congratulations! The robot has found the exit!\n";
            gameOver = true;
            continue;
        }

        // Check minotaur interaction
        if (minotaur->getIsAlive()) {
            int robotReachable = minotaur->checkIfRobotIsReachable(
                *labyrinth,
                robot->getPowerUps().hasShield(),
                robot->getPowerUps().hasSword()
            );

            if (robotReachable == 1) {
                std::cout << "Game Over! The Minotaur caught the robot.\n";
                gameOver = true;
                continue;
            }
            else if (robotReachable == 2) {
                std::cout << "The robot killed the Minotaur with the sword!\n";
                // Minotaur is now dead, no need for further checks
            }
        }

        // Minotaur move (only if alive)
        if (minotaur->getIsAlive()) {
            char minotaurMoveValid = minotaur->move(*labyrinth);
            while (minotaurMoveValid == 'I') {
                minotaurMoveValid = minotaur->move(*labyrinth);
            }
        }

        // Decrement power-up turns at the end of each turn
        robot->decrementPowerUpTurns();

    }

    std::cout << "Game Over!\n";
}

void Game::display() const {
    system("cls");  // Clear screen

    if (robot->getPowerUps().hasFog()) {
        std::cout << "Fog is active - limited visibility!\n";
        labyrinth->displayWithFog(robot->getPosition());
    }
    else {
        labyrinth->display();
    }
}