#ifndef LAWN_HPP
#define LAWN_HPP

#include "../tetra/base.hpp"
#include "../tetra/array.hpp"
#include "../tetra/optional.hpp"

#include "coordinate.hpp"
#include "lane.hpp"

using namespace te;

class Lawn {
private:
    Array<Lane> lawn;

public:
    Lawn();

    Coordinate getCoordinates(ref<str> symbol) const;
    str getSymbol(ref<Coordinate> coord) const;

    void replace(ref<Coordinate> coord, ref<str> symbol);
    void swap(ref<Coordinate> coordA, ref<Coordinate> coordB);
    void trail(ref<Coordinate> coordA, ref<Coordinate> coordB);

    void print() const;
    void lineSeparator() const;
    // New method to print with navigator
    void printWithNavigator(const Coordinate& navigator) const;

    Array<int> tileIndices(int laneIndex) const;
};

#endif // LAWN_HPP