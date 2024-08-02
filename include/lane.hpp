#ifndef LANE_HPP
#define LANE_HPP

#include "../tetra/base.hpp"
#include "../tetra/optional.hpp"
#include "../tetra/array.hpp"

class Lane {
    friend class Lawn;
private:
    te::Array<te::str> tiles;

public:
    Lane();

    te::optional<int> index(te::ref<te::str> symbol) const;
    te::str symbol(int tileIndex) const;
    void replace(int x, te::ref<te::str> symbol);
    void print() const;
};

#endif // LANE_HPP