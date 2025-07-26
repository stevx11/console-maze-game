/*
 * Game.h - Main game controller class
 * Handles game loop and entity interactions
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef GAME_H
#define GAME_H

#include "../labyrinth/Labyrinth.h"
#include <utility>
#include <string>
#include "Robot.h"
#include "Minotaur.h"

 /*
  * Main game controller that orchestrates the labyrinth game
  * Manages the game loop and coordinates all entities
  */
class Game {
private:
    Labyrinth* labyrinth;              // Game labyrinth
    Robot* robot;                      // Player's robot
    Minotaur* minotaur;               // Enemy minotaur
    bool gameOver;                     // Game end flag
    std::pair<int, int> LabyrinthExit; // Exit coordinates
    std::string gameOutcome;           // Final game result

public:
    // Constructor, initializes game with labyrinth
    Game(Labyrinth* lab);

    // Destructor 
    ~Game();

    // Main game loop
    void run();

    // Display current game state to console
    void display() const;

private:
    // Write final game report with labyrinth visualization
    void writeGameReport();
};

#endif // GAME_H