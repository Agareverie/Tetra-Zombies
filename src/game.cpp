#include "../include/game.hpp"
#include "../tetra/time.hpp"

Game::Game() : lawn(), isRunning(true), sun(0) {
    sunThread = std::thread(&Game::incrementSunCount, this);
}

Game::~Game() {
    isRunning = false;
    if (sunThread.joinable()) {
        sunThread.join();
    }
}

void Game::incrementSunCount() {
    while (isRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        sun += 25; // Increment sun count
    }
}

int Game::getSun() {
    return sun;
}

void Game::summonZombie(std::mt19937& rng) {
    std::uniform_int_distribution<int> laneDist(0, 4);

    int laneIndex = laneDist(rng);
    int tileIndex = 9;

    Coordinate zombieCoord = Coordinate(laneIndex, tileIndex);
    auto newZombie = std::make_shared<Zombie>(zombieCoord, 5); // Example HP value
    
    if (lawn.getSymbol(zombieCoord) == " ") {
        // Place zombie on the lawn and add to zombies vector
        zombies.push_back(newZombie);
        lawn.replace(zombieCoord, "Z");

        // Pass weak_ptr to the thread
        std::weak_ptr<Zombie> weakZombie = newZombie;
        std::thread zombieThread([this, weakZombie] {
            while (true) {
                if (auto zombie = weakZombie.lock()) { // Try to lock weak_ptr
                    updateZombiePosition(zombie);
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                } else {
                    break; // Exit the loop if the zombie no longer exists
                }
            }
        });
        zombieThread.detach(); // Detach the thread if you don't need to join it later
    }
}

void Game::updateZombiePosition(std::shared_ptr<Zombie> zombie) {
    Coordinate oldLocation = zombie->getLocation();
    Coordinate newLocation = oldLocation.left();
    if (lawn.getSymbol(newLocation) == " ") {
        lawn.replace(oldLocation, " "); // Clear old position
        lawn.replace(newLocation, "Z"); // Place zombie in new position
        zombie->moveLeft();
    }
}

void Game::updateLawn() {
    // std::thread updateThread([this] {
    //     while (isRunning) {
    //         std::cout << "Updating zombies..." << std::endl; // Debug output

    //         for (auto& zombie : zombies) {
    //             std::this_thread::sleep_for(std::chrono::seconds(1));
    //             updateZombiePosition(zombie);
    //         }

    //         std::this_thread::sleep_for(std::chrono::seconds(3)); // Sleep for 3 seconds
    //     }
    // });

    // updateThread.detach(); // Detach the thread if you don't need to join it later
}

Array<std::shared_ptr<Zombie>> Game::getZombies() {
    return zombies;
}

void Game::start() {
    if (!isRunning) {
        cout << "Game is not running!" << "\n";
        return;
    }
    cout << "Game started!" << "\n";
    lawn.print();
}

void Game::endGame() {
    if (isRunning) {
        isRunning = false;
        cout << "Game Over!" << "\n";
    }
}

void Game::place(Lawn& lawn, ref<Coordinate> coord, ref<str> symbol) {
    if (!isRunning) {
        cout << "Game is not running!" << "\n";
        return;
    }
    lawn.replace(coord, symbol);
    cout << "Placed \"" << symbol << "\" at ";
    coord.print();
    cout << "\n";
}

void Game::shovelTile(Lawn& lawn, ref<Coordinate> coord) {
    if (!isRunning) {
        cout << "Game is not running!" << "\n";
        return;
    }
    lawn.replace(coord, " ");
    cout << "Shovelled tile" << " at ";
    coord.print();
    cout << "\n";
}

void Game::swap(Lawn& lawn, ref<Coordinate> coordA, ref<Coordinate> coordB) {
    lawn.swap(coordA, coordB);

    cout << "Swapped \"" << lawn.getSymbol(coordB) << "\" at ";
    coordA.print();
    cout << " with \"" << lawn.getSymbol(coordA) << "\" at ";
    coordB.print();
    cout << "\n";
}

void Game::trail(Lawn& lawn, ref<Coordinate> coordA, ref<Coordinate> coordB) {
    lawn.trail(coordA, coordB);

    cout << "Moved \"" << lawn.getSymbol(coordB) << "\" to ";
    coordB.print();
    cout << "\n";
}

Lawn& Game::getLawn() {
    return lawn;
}