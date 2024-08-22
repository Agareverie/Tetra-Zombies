#include "zombie.hpp"

Zombie::Zombie(Coordinate loc, int initialHP) 
    : location(loc), hp(initialHP) {}

Zombie::~Zombie() {
    stop();
}

void Zombie::moveLeft() {
    location = location.left();
}

void Zombie::start() {
    running = true;
    movementThread = std::thread(&Zombie::run, this);
}

void Zombie::stop() {
    if (running) {
        running = false;
        if (movementThread.joinable()) {
            movementThread.join();
        }
    }
}

Coordinate Zombie::getLocation() const {
    return location;
}

int Zombie::getHP() const {
    return hp;
}

void Zombie::takeDamage(int damage) {
    hp -= damage;
    if (hp <= 0) {
        hp = 0;
        // Implement behavior for when zombie dies, if needed
    }
}

bool Zombie::isDead() const {
    return hp <= 0;
}
bool Zombie::isAlive() const {
    return hp > 0;
}

char Zombie::getSymbol() const {
    switch (isDead()) {
        case true: 
            return ' ';
        case false:
            return 'Z';
    }
}

void Zombie::run() {
    while (running) {
        moveLeft(); // Move zombie to the left
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}
