#include "Game.h"
#include <iostream>

Game::Game(Labyrinth* lab)
    : labyrinth(lab), gameOver(false)
{
    LabyrinthExit = labyrinth->getExit();
    robot = new Robot({1,labyrinth->getEntry().second});
    std::pair<int, int> minotaurStartPosition = labyrinth->getRandomPosition();
    minotaur = new Minotaur(minotaurStartPosition);
    labyrinth->changeGrid(minotaurStartPosition, 'M');
}

Game::~Game() {
    delete labyrinth;
}

void Game::run() {
    while (!gameOver) {
        display();
        const Item* item = labyrinth->getItemAt(robot->getPosition());
        if (item) {
            std::cout << "Robot found an item: " << item->getEffect() << "\n";
        }
        char robotMoveValid = robot->move(*labyrinth);

        if (robotMoveValid == 'Q') {
            std::cout << "You chose to quit the game\n";
            gameOver = true;
            continue;
        }
        else if (robotMoveValid == 'I') {
            continue;
        }
        int isRobotReachable = minotaur->checkIfRobotIsReachable(*labyrinth);
        if (isRobotReachable == 1) {
            std::cout << "Game Over! The Minotaur destroyed the robot.\n";
            gameOver = true;
            continue;
        }
        char minotaurMoveValid = minotaur->move(*labyrinth);
        while (minotaurMoveValid == 'I') {
            minotaurMoveValid = minotaur->move(*labyrinth);
        }
        // Check the game state
        if (robot->getPosition() == LabyrinthExit) {
            std::cout << "Congratulations! The robot has found the exit!\n";
            gameOver = true;
        }

        std::cout << "Game Over!\n";
    }
}


void Game::display() const {
    system("cls");
    labyrinth->display();
}
