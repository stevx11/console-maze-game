#ifndef GAME_H
#define GAME_H

#include "../labyrinth/Labyrinth.h"
#include <utility>
#include <string>
#include "Robot.h"
#include "Minotaur.h"

class Game {
private:
    Labyrinth* labyrinth;
    Robot* robot;
    Minotaur* minotaur;
    bool gameOver;
    std::pair<int, int> LabyrinthExit;

public:
    Game(Labyrinth* lab);
    ~Game();

    void run();             // Main game loop
    void display() const;   // Display game state
};

#endif // GAME_H