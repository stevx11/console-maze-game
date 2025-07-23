// Items.h
#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <utility>
#include <vector>

// Base class for all items
class Item {
protected:
    std::pair<int, int> position;

public:
    Item(const std::pair<int, int>& pos) : position(pos) {}
    virtual ~Item() = default;
    virtual std::string getEffect() const = 0;
    std::pair<int, int> getPosition() const { return position; }
};

// Derived class: Sword
class Sword : public Item {
public:
    Sword(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Sword: Can destroy the Minotaur."; }
};

// Derived class: Shield
class Shield : public Item {
public:
    Shield(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Shield: Protects from the Minotaur."; }
};

// Derived class: Hammer
class Hammer : public Item {
public:
    Hammer(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Hammer: Can break walls."; }
};

// Derived class: Fog
class Fog : public Item {
public:
    Fog(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Fog: Reduces visibility to a 3x3 area."; }
};

#endif // ITEMS_H