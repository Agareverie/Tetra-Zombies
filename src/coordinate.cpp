#include "../include/coordinate.hpp"
#include <iostream>

Coordinate::Coordinate(int lane, int tile) : lane(lane), tile(tile) {}

int Coordinate::clampLane(int lane) {
    return std::clamp(lane, 0, 4);
}

int Coordinate::clampTile(int tile) {
    return std::clamp(tile, 0, 9);
}

Coordinate Coordinate::up() const {
    return Coordinate(clampLane(lane - 1), tile);
}

Coordinate Coordinate::down() const {
    return Coordinate(clampLane(lane + 1), tile);
}

Coordinate Coordinate::left() const {
    return Coordinate(lane, clampTile(tile - 1));
}

Coordinate Coordinate::right() const {
    return Coordinate(lane, clampTile(tile + 1));
}

void Coordinate::print() const {
    std::cout << "(" << lane << ", " << tile << ")"; // (3, 5)
}