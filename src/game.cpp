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
    Zombie newZombie = Zombie(zombieCoord, 5); // Example HP
    
    if (lawn.getSymbol(zombieCoord) == " ") {
        // Create a new Zombie and place it on the lawn
        Zombie newZombie(zombieCoord, 100); // Example HP value
        zombies.push_back(newZombie); // Add zombie to the game
        lawn.replace(zombieCoord, "Z"); // Place zombie symbol on the lawn
    }
}

ref<Array<Zombie>> Game::getZombies() {
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