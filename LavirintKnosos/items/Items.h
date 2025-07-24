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
    virtual std::string getType() const = 0;
    std::pair<int, int> getPosition() const { return position; }
};

// Derived class: Sword
class Sword : public Item {
public:
    Sword(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Sword: Can destroy the Minotaur for 3 turns."; }
    std::string getType() const override { return "SWORD"; }
};

// Derived class: Shield
class Shield : public Item {
public:
    Shield(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Shield: Protects from the Minotaur for 3 turns."; }
    std::string getType() const override { return "SHIELD"; }
};

// Derived class: Hammer
class Hammer : public Item {
public:
    Hammer(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Hammer: Can break walls for 3 turns."; }
    std::string getType() const override { return "HAMMER"; }
};

// Derived class: Fog
class Fog : public Item {
public:
    Fog(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Fog: Reduces visibility to a 3x3 area for 3 turns."; }
    std::string getType() const override { return "FOG"; }
};

// Power-up manager class
class PowerUpManager {
private:
    int swordTurns;
    int shieldTurns;
    int hammerTurns;
    int fogTurns;

public:
    PowerUpManager() : swordTurns(0), shieldTurns(0), hammerTurns(0), fogTurns(0) {}

    void activateSword() { swordTurns = 3; }
    void activateShield() { shieldTurns = 3; }
    void activateHammer() { hammerTurns = 3; }
    void activateFog() { fogTurns = 3; }

    bool hasSword() const { return swordTurns > 0; }
    bool hasShield() const { return shieldTurns > 0; }
    bool hasHammer() const { return hammerTurns > 0; }
    bool hasFog() const { return fogTurns > 0; }

    void decrementTurns() {
        if (swordTurns > 0) swordTurns--;
        if (shieldTurns > 0) shieldTurns--;
        if (hammerTurns > 0) hammerTurns--;
        if (fogTurns > 0) fogTurns--;
    }

    int getSwordTurns() const { return swordTurns; }
    int getShieldTurns() const { return shieldTurns; }
    int getHammerTurns() const { return hammerTurns; }
    int getFogTurns() const { return fogTurns; }

    std::string getActiveEffects() const {
        std::string effects = "";
        if (hasSword()) effects += "Sword(" + std::to_string(swordTurns) + ") ";
        if (hasShield()) effects += "Shield(" + std::to_string(shieldTurns) + ") ";
        if (hasHammer()) effects += "Hammer(" + std::to_string(hammerTurns) + ") ";
        if (hasFog()) effects += "Fog(" + std::to_string(fogTurns) + ") ";
        return effects;
    }
};

#endif // ITEMS_H