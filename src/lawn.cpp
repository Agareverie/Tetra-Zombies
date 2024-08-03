#include "../include/lawn.hpp"

using namespace te;

Lawn::Lawn() : lawn(5) {}

void Lawn::lineSeparator() const {
    cout << "--+---+---+---+---+---+---+---+---+---+" << "\n";
}

Coordinate Lawn::getCoordinates(ref<str> symbol) const {
    for (int laneIndex : indices(lawn)) {
        optional<int> tileIndex = lawn[laneIndex].index(symbol);
        if (tileIndex) {
            return Coordinate(laneIndex, tileIndex.value());
        }
    }
    return Coordinate(-1, -1);
}

str Lawn::getSymbol(ref<Coordinate> coord) const {
    return lawn[coord.lane].symbol(coord.tile);
}

void Lawn::replace(ref<Coordinate> coord, ref<str> symbol) {
    if (coord.lane >= 0 && coord.lane < lawn.size()) {
        lawn[coord.lane].replace(coord.tile, symbol);
    }
}

void Lawn::swap(ref<Coordinate> coordA, ref<Coordinate> coordB) {
    str temp_symbol = getSymbol(coordB);
    replace(coordB, getSymbol(coordA));
    replace(coordA, temp_symbol);
    temp_symbol.clear();
}

void Lawn::trail(ref<Coordinate> coordA, ref<Coordinate> coordB) {
    replace(coordB, getSymbol(coordA));
    replace(coordA, " ");
}

void Lawn::print() const {
    lineSeparator();     // --+---+---+---+---+---+---+---+---+---+
    for (ref<Lane> lane : lawn) {
        lane.print();    // M |   |   |   |   |   |   |   |   |   | 
        lineSeparator(); // --+---+---+---+---+---+---+---+---+---+
    }
}

Array<int> Lawn::tileIndices(int laneIndex) const {
    return indices(lawn[laneIndex].tiles);
}

void Lawn::printWithNavigator(ref<Coordinate> navigator) const {
    const str RESET_COLOR = "\033[0m";
    const str RED_COLOR = "\033[31m";

    lineSeparator();
    for (int laneIndex : indices(lawn)) {
        for (int tileIndex : indices(lawn[laneIndex].tiles)) {
            if (laneIndex == navigator.lane && tileIndex == navigator.tile) {
                if (lawn[laneIndex].symbol(tileIndex) != " ") {
                    std::cout << RED_COLOR << "o" << RESET_COLOR << " | "; // Navigator is red
                } else {
                    std::cout << "o | "; // Display navigation symbol
                }
            } else {
                std::cout << lawn[laneIndex].symbol(tileIndex) << " | ";
            }
        }
        std::cout << std::endl;
        lineSeparator();
    }
}