#ifndef GAME_HPP
#define GAME_HPP

#include "../tetra/base.hpp"
#include "../tetra/array.hpp"
#include "../tetra/optional.hpp"

#include "coordinate.hpp"
#include "zombie.hpp"
#include "lane.hpp"
#include "lawn.hpp"

#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <memory>
#include <random>


using namespace te;

class Game {
private:
    Lawn lawn;
    std::thread sunThread;
    std::atomic<bool> isRunning;
    std::mutex sunMutex;
    int sun;
    Array<std::shared_ptr<Zombie>> zombies;  // Container to manage zombies
    std::mutex zombieMutex;
    bool cherryBombExploding = false;

public:
    Game();  // Constructor
    ~Game();
    

public:
    void start();
    void endGame();

    virtual void incrementSunCount();
    int getSun();
    void summonZombie(std::mt19937& rng);
    Array<std::shared_ptr<Zombie>> getZombies();
    void updateZombiePosition(std::shared_ptr<Zombie> zombie);
    void removeZombie(std::shared_ptr<Zombie> zombie);
    Lawn& getLawn(); // Add this method if needed

    void startZombieSpawner(std::mt19937& rng);
    void cherryBombExplodes();
    void removeZombieAtCoordinate(ref<Coordinate> coord);
    void trail(Lawn& lawn, ref<Coordinate> coordA, ref<Coordinate> coordB);
};

#endif // GAME_HPP