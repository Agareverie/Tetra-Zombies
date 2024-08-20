#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "coordinate.hpp"

class Zombie {
public:
    Zombie(Coordinate loc, int initialHP);
    ~Zombie();

    // Method to get the zombie's location
    Coordinate getLocation() const;

    // Method to get the zombie's HP
    int getHP() const;

    // Method to decrement the zombie's HP
    void takeDamage(int damage);

    // Method to check if the zombie is dead
    bool isDead() const;

    // Method to get the zombie's symbol
    char getSymbol() const;

private:
    Coordinate location;  // The zombie's position on the lawn
    int hp;               // The zombie's hit points
};

#endif // ZOMBIE_HPP