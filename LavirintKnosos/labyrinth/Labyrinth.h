#ifndef LABYRINTH_H
#define LABYRINTH_H
#include "../items/Items.h"
#include <vector>
#include <string>
#include <memory>

class Labyrinth {
private:
    int rows;
    int columns;
    int numberOfItems;
    std::pair<int, int> startAndEndColumn;
    char** grid;
    std::vector<std::vector<Item*>> items;

public:
    Labyrinth(int r, int c, int items, std::pair<int, int> startAndEndColumn);
    ~Labyrinth();

    void generateOuterWalls();
    void placeRobotAndExit();
    void generateInnerWalls();
    void ensurePassability();
    void placeItems();
    void clearItems();
    void display() const;
    void displayWithFog(const std::pair<int, int>& robotPosition) const;
    std::pair<int, int> getEntry() const;
    std::pair<int, int> getExit() const;
    std::pair<int, int> getRandomPosition() const;
    char getCell(const std::pair<int, int>& position) const;
    int getRows() const;
    int getColumns() const;
    void changeGrid(const std::pair<int, int>& position, char changeTo);
    const Item* getItemAt(const std::pair<int, int>& position) const;
    void removeItemAt(const std::pair<int, int>& position);
};

#endif // LABYRINTH_H