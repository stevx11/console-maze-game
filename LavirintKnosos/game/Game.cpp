/*
 * Game.cpp - Implementation of main game controller
 * Contains game loop logic and entity coordination
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#include "Game.h"
#include <iostream>
#include <sstream>
#include "../utils/Utils.h"

Game::Game(Labyrinth* lab)
    : labyrinth(lab), gameOver(false)
{
    // Store exit coordinates for win condition checking
    LabyrinthExit = labyrinth->getExit();

    // Create robot at the labyrinth entry point
    robot = new Robot({ 1, labyrinth->getEntry().second });

    // Create minotaur at a random valid position
    std::pair<int, int> minotaurStartPosition = labyrinth->getRandomPosition();
    minotaur = new Minotaur(minotaurStartPosition);

    // Place minotaur symbol on the labyrinth grid
    labyrinth->changeGrid(minotaurStartPosition, 'M');
}

Game::~Game() {
    writeGameReport();

    delete robot;
    delete minotaur;
    delete labyrinth;
}

void Game::run() {
    // Display welcome message and controls
    std::cout << "Welcome to the Labyrinth of Knossos!\n";
    std::cout << "Controls: W/A/S/D to move, Q to quit\n";
    std::cout << "Find items (P) to gain powers, reach the exit (I) to win!\n\n";

    // Main game loop
    while (!gameOver) {
        display();

        // Show active power-ups to the player
        std::string activeEffects = robot->getPowerUps().getActiveEffects();
        if (!activeEffects.empty()) {
            std::cout << "Active effects: " << activeEffects << "\n";
        }

        // Check if robot is standing on an item
        const Item* item = labyrinth->getItemAt(robot->getPosition());
        if (item) {
            std::cout << "Robot found an item: " << item->getEffect() << "\n";
            robot->collectItem(item);
            labyrinth->removeItemAt(robot->getPosition());
        }

        // Process robot movement
        char robotMoveValid = robot->move(*labyrinth);

        // Handle quit command
        if (robotMoveValid == 'Q') {
            std::cout << "You chose to quit the game\n";
            gameOutcome = "QUIT";
            gameOver = true;
            continue;
        }
        // Handle invalid move
        else if (robotMoveValid == 'I') {
            continue; // Invalid move, try again
        }

        else if (robotMoveValid == 'K') {
            std::cout << "The robot killed the Minotaur with the sword!\n";
            minotaur->setIsAlive(false);
        }

        // Check win condition
        if (robot->getPosition() == LabyrinthExit) {
            std::cout << "Congratulations! The robot has found the exit!\n";
            gameOutcome = "WIN";
            gameOver = true;
            continue;
        }

        // Handle minotaur interactions if minotaur is alive
        if (minotaur->getIsAlive()) {
            int robotReachable = minotaur->checkIfRobotIsReachable(
                *labyrinth,
                robot->getPowerUps().hasShield(),
                robot->getPowerUps().hasSword()
            );

            if (robotReachable == 1) {
                std::cout << "Game Over! The Minotaur caught the robot.\n";
                gameOutcome = "LOSS";
                gameOver = true;
                continue;
            }
            else if (robotReachable == 2) {
                std::cout << "The robot killed the Minotaur with the sword!\n";
                // Minotaur is now dead no need for further checks
            }
            else if (robotReachable == 3) {
                std::cout << "The robot is protected by the shield!\n";
                continue;
            }
        }

        // Move minotaur if still alive
        if (minotaur->getIsAlive()) {
            char minotaurMoveValid = minotaur->move(*labyrinth);
            // Retry movement if invalid
            while (minotaurMoveValid == 'I') {
                minotaurMoveValid = minotaur->move(*labyrinth);
            }
        }

        // Decrement powerup duration at end of turn
        robot->decrementPowerUpTurns();
    }

    std::cout << "Game Over!\n";
}

void Game::display() const {
    system("cls");  // Clear screen

    // Display with fog effect if active otherwise normal display
    if (robot->getPowerUps().hasFog()) {
        std::cout << "Fog is active - limited visibility!\n";
        labyrinth->displayWithFog(robot->getPosition());
    }
    else {
        labyrinth->display();
    }
}

// Write comprehensive game report with final labyrinth visualization
void Game::writeGameReport() {
    std::stringstream report;

    report << "\n========== GAME SESSION REPORT ==========\n";
    report << "Game Outcome: " << gameOutcome << "\n";
    report << "\n--------- COMPLETE LABYRINTH ---------\n";
    report << Utils::labyrinthToString(*labyrinth);
    report << "\n==========================================\n\n";

    // Write to game session log
    std::string gameLogFilename = "game_session_log.txt";
    Utils::appendToFile(gameLogFilename, report.str());
}