#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <algorithm>

struct Coordinate {
    int lane, tile;

    Coordinate(int lane, int tile);

    static int clampLane(int lane);
    static int clampTile(int tile);

    Coordinate up()    const;
    Coordinate down()  const;
    Coordinate left()  const;
    Coordinate right() const;

    void print() const;
};

#endif // COORDINATE_HPP