#ifndef GAME_HPP
#define GAME_HPP

#include "../tetra/base.hpp"
#include "../tetra/array.hpp"
#include "../tetra/optional.hpp"

#include "coordinate.hpp"
#include "lane.hpp"
#include "lawn.hpp"

#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

using namespace te;

class Game {
private:
    Lawn lawn;
    std::thread sunThread;
    std::atomic<bool> isRunning;
    std::mutex sunMutex;
    int sun;

public:
    Game();  // Constructor

protected:
    virtual ~Game(); // Destructor

public:
    void start();
    void endGame();

    virtual void incrementSunCount();
    int getSun();

    void place(Lawn& lawn, ref<Coordinate> coord, ref<str> symbol);
    void shovelTile(Lawn& lawn, ref<Coordinate> coord);
    // Game wrappers for Lawn
    void swap(Lawn& lawn, ref<Coordinate> coordA, ref<Coordinate> coordB);
    void trail(Lawn& lawn, ref<Coordinate> coordA, ref<Coordinate> coordB);

protected:
    Lawn& getLawn(); // Add this method if needed
};

#endif // GAME_HPP