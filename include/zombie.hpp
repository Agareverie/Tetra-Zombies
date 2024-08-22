#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#pragma once
#include <thread>
#include <chrono>
#include "coordinate.hpp"

class Zombie {
public:
    Zombie(Coordinate loc, int initialHP);
    ~Zombie();

    void moveLeft();
    void start();
    void stop();

    // Method to get the zombie's location
    Coordinate getLocation() const;

    // Method to get the zombie's HP
    int getHP() const;

    // Method to decrement the zombie's HP
    void takeDamage(int damage);

    // Method to check if the zombie is dead
    bool isDead() const;
    bool isAlive() const;

    // Method to get the zombie's symbol
    char getSymbol() const;

private:
    Coordinate location;
    int hp;
    std::thread movementThread;
    bool running = false;

    void run();
};

#endif // ZOMBIE_HPP