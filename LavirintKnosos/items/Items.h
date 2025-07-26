/*
 * Items.h - Item system and powerup management
 * Defines all collectible items and their effects
 * Author: SV65/2023
 * Last modified: 26.07.2025
 */

#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <utility>
#include <vector>

 /*
  * Base class for all collectible items
  * Provides interface for item effects and positioning
  */
class Item {
protected:
    std::pair<int, int> position;    // Item position in labyrinth

public:
    Item(const std::pair<int, int>& pos) : position(pos) {}
    virtual ~Item() = default;

    // Get item description text
    virtual std::string getEffect() const = 0;

    // Get item type identifier
    virtual std::string getType() const = 0;

    // Get item position
    std::pair<int, int> getPosition() const { return position; }
};

// Sword - Can destroy the Minotaur for 3 turns
class Sword : public Item {
public:
    Sword(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Sword: Can destroy the Minotaur for 3 turns."; }
    std::string getType() const override { return "SWORD"; }
};

// Shield - Protects from the Minotaur for 3 turns
class Shield : public Item {
public:
    Shield(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Shield: Protects from the Minotaur for 3 turns."; }
    std::string getType() const override { return "SHIELD"; }
};

// Hammer - Can break walls for 3 turns
class Hammer : public Item {
public:
    Hammer(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Hammer: Can break walls for 3 turns."; }
    std::string getType() const override { return "HAMMER"; }
};

// Fog - Reduces visibility to 3x3 area for 3 turns
class Fog : public Item {
public:
    Fog(const std::pair<int, int>& pos) : Item(pos) {}
    std::string getEffect() const override { return "Fog: Reduces visibility to a 3x3 area for 3 turns."; }
    std::string getType() const override { return "FOG"; }
};

/*
 * Powerup manager class
 * Tracks active powerups and their remaining duration
 */
class PowerUpManager {
private:
    int swordTurns;      // Remaining sword turns
    int shieldTurns;     // Remaining shield turns
    int hammerTurns;     // Remaining hammer turns
    int fogTurns;        // Remaining fog turns

public:
    PowerUpManager() : swordTurns(0), shieldTurns(0), hammerTurns(0), fogTurns(0) {}

    // Activate powerups (sets to 3 turns)
    void activateSword() { swordTurns = 3; }
    void activateShield() { shieldTurns = 3; }
    void activateHammer() { hammerTurns = 3; }
    void activateFog() { fogTurns = 3; }

    // Check if powerups are active
    bool hasSword() const { return swordTurns > 0; }
    bool hasShield() const { return shieldTurns > 0; }
    bool hasHammer() const { return hammerTurns > 0; }
    bool hasFog() const { return fogTurns > 0; }

    // Decrement all active powerup counters
    void decrementTurns() {
        if (swordTurns > 0) swordTurns--;
        if (shieldTurns > 0) shieldTurns--;
        if (hammerTurns > 0) hammerTurns--;
        if (fogTurns > 0) fogTurns--;
    }

    // Get remaining turns for each powerup
    int getSwordTurns() const { return swordTurns; }
    int getShieldTurns() const { return shieldTurns; }
    int getHammerTurns() const { return hammerTurns; }
    int getFogTurns() const { return fogTurns; }

    // Get formatted string of active effects
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