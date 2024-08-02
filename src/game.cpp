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
        Time::sleep(5); // Wait for 5 seconds
        
        std::lock_guard<std::mutex> lock(sunMutex);
        sun += 25; // Increment sun count
    }
}

int Game::getSun() {
    std::lock_guard<std::mutex> lock(sunMutex);
    return sun;
}
void Game::start() {
    if (!isRunning) {
        cout << "Game is not running!" << endl;
        return;
    }
    cout << "Game started!" << endl;
    lawn.print();
}

void Game::endGame() {
    if (isRunning) {
        isRunning = false;
        cout << "Game Over!" << endl;
    }
}

void Game::place(Lawn& lawn, ref<Coordinate> coord, ref<str> symbol) {
    if (!isRunning) {
        cout << "Game is not running!" << endl;
        return;
    }
    lawn.replace(coord, symbol);
    cout << "Placed \"" << symbol << "\" at ";
    coord.print();
    cout << endl;
}

void Game::shovelTile(Lawn& lawn, ref<Coordinate> coord) {
    if (!isRunning) {
        cout << "Game is not running!" << endl;
        return;
    }
    lawn.replace(coord, " ");
    cout << "Shovelled tile" << " at ";
    coord.print();
    cout << endl;
}

void Game::swap(Lawn& lawn, ref<Coordinate> coordA, ref<Coordinate> coordB) {
    lawn.swap(coordA, coordB);

    cout << "Swapped \"" << lawn.getSymbol(coordB) << "\" at ";
    coordA.print();
    cout << " with \"" << lawn.getSymbol(coordA) << "\" at ";
    coordB.print();
    cout << endl;
}

void Game::trail(Lawn& lawn, ref<Coordinate> coordA, ref<Coordinate> coordB) {
    lawn.trail(coordA, coordB);

    cout << "Moved \"" << lawn.getSymbol(coordB) << "\" to ";
    coordB.print();
    cout << endl;
}

Lawn& Game::getLawn() {
    return lawn;
}