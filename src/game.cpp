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
                // Try to lock the weak_ptr to a shared_ptr
                if (auto zombie = weakZombie.lock()) {
                    std::this_thread::sleep_for(std::chrono::seconds(3)); // Sleep before moving
                    
                    // Check for cherry bomb explosion
                    if (cherryBombExploding) {
                        cherryBombExploding = false; // Reset flag
                        break; // Exit thread if cherry bomb exploded
                    }

                    // Update zombie position
                    updateZombiePosition(zombie);
                } else {
                    break; // Exit the loop if the zombie is no longer valid
                }
            }
        });
        zombieThread.detach(); // Detach the thread if you don't need to join it later
    }
}

void Game::updateZombiePosition(std::shared_ptr<Zombie> zombie) {

    if (zombie == nullptr) {
        return; // Zombie has been removed or is invalid
    }

    Coordinate oldLocation = zombie->getLocation();
    Coordinate newLocation = oldLocation.left();
    char targetSymbol = lawn.getSymbol(newLocation)[0];

    switch (targetSymbol) {
        case ' ':
            lawn.replace(oldLocation, " "); // Clear old position
            lawn.replace(newLocation, "Z"); // Place zombie in new position
            zombie->moveLeft();
            break;
        case 'S':
        case 'P':
        case 'v':
            lawn.replace(newLocation, " "); // Remove the plant from the lawn
            break;
        case 'W':
            lawn.replace(newLocation, "w"); // Degrade to lower-case w
            break;
        case 'w':
            lawn.replace(newLocation, "v"); // Degrade to lower-case w
            break;
        case 'M':
            lawn.replace(oldLocation, " ");
            lawn.replace(oldLocation, " ");
            zombie->stop();
            break;
        default:
            break;
    }
}

void Game::removeZombie(std::shared_ptr<Zombie> zombie) {
    std::lock_guard<std::mutex> lock(zombieMutex); // Ensure thread safety
    // Remove the zombie from the vector
    zombies.erase(std::remove_if(zombies.begin(), zombies.end(),
                                 [&zombie](const std::shared_ptr<Zombie>& z) {
                                     return z == zombie;
                                 }),
                  zombies.end());
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

// In your Game class
void Game::startZombieSpawner(std::mt19937& rng) {
    std::thread([this, &rng]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(10)); // Wait for 10 seconds
            summonZombie(rng); // Summon a new zombie
        }
    }).detach(); // Detach the thread to run independently
}


void Game::cherryBombExplodes() {
    // Get the location of the Cherry Bomb
    const Coordinate coord = lawn.getCoordinates("C");

    if (coord.lane == -1 && coord.tile == -1) {
        return;
    }

    cherryBombExploding = true;
    Time::sleep(0.5);

    std::cout << "CHA-BOOF!!" << std::endl; 
    
    // Define the area affected by the explosion
    Array<Coordinate> aroundArea = {
        coord.up().left(), coord.up(), coord.up().right(),
        coord.left(), coord, coord.right(),
        coord.down().left(), coord.down(), coord.down().right()
    };

    // Remove plants and zombies in the explosion area
    for (const auto& c : aroundArea) {
        getLawn().replace(c, " ");  // Replace with empty space
        removeZombieAtCoordinate(c);  // Remove any zombies at this coordinate
    }
}

void Game::removeZombieAtCoordinate(ref<Coordinate> coord) {
    for (auto it = zombies.begin(); it != zombies.end(); ) {
        Coordinate zombieCoord = (*it)->getLocation();
        if (zombieCoord.lane == coord.lane &&
            zombieCoord.tile == coord.tile) {
            (*it)->stop();
            it = zombies.erase(it);  // Remove the zombie and update the iterator
        } else {
            ++it;  // Move to the next zombie
        }
    }
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