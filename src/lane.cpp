#include "../include/lane.hpp"

Lane::Lane() : tiles(10, " ") { 
    tiles[0] = "M"; 
}

te::optional<int> Lane::index(te::ref<te::str> symbol) const {
    for (int i : te::indices(tiles)) {
        if (tiles[i] == symbol) { 
            return i; 
        }
    }
    return te::None;
}

te::str Lane::symbol(int tileIndex) const { 
    return tiles[tileIndex]; 
}

void Lane::replace(int x, te::ref<te::str> symbol) { 
    tiles[x] = symbol; 
}

void Lane::print() const {
    for (te::ref<te::str> tile : tiles) {
        te::cout << tile << " | ";
    }
    te::cout << "\n"; 
}