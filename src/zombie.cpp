#include "zombie.hpp"

Zombie::Zombie(Coordinate loc, int initialHP) 
    : location(loc), hp(initialHP) {}

Zombie::~Zombie() {
    // No dynamic resources to clean up
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

char Zombie::getSymbol() const {
    switch (isDead()) {
        case true: 
            return ' ';
        case false:
            return 'Z';
    }
}