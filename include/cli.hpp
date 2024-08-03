#ifndef CLI_HPP
#define CLI_HPP

#include "game.hpp"
#include <conio.h> // For _getch()

using namespace te;

class CLI : public Game {
public:

    CLI();

    virtual ~CLI();

    int sun;
    std::thread uiThread;
    std::atomic<bool> uiRunning;
    str buffer;
    str previousBuffer; // Previous buffer to check for changes

    void run(); // Start the CLI interface
private:
    // Define constants for key codes
    static const int ARROW_PREFIX = 224;
    static const int UP_ARROW = 72;
    static const int DOWN_ARROW = 80;
    static const int LEFT_ARROW = 75;
    static const int RIGHT_ARROW = 77;
    static const int ENTER_KEY = 13;
    static const int ESCAPE_KEY = 27;

    // Define options
    enum Option {
        OPTION_PLANT1,   // Sunflower
        OPTION_PLANT2,   // Escape Root
        OPTION_PLANT3,   // Peashooter
        OPTION_PLANT4,   // Cherry Bomb
        OPTION_PLANT5,   // Wall-Nut
        OPTION_SWAP_ESCAPE_ROOT,
        OPTION_SHOVEL,
        OPTION_EXIT,
        OPTION_COUNT
    };
    

    void navigateLawn(Option action);
    void plant(Coordinate& navigator, ref<str> symbol);
    void swapEscapeRoot(Coordinate& navigator);
    void shovel(Coordinate& navigator);
    
    void printInterface();
    void printMenuOption(std::ostringstream& oss, Option currentSelection, Option option, ref<str> text);
    void printLawnRow(std::ostringstream& oss, int laneIndex);

    void clearScreen();
    void resetUI();
    void updateUI();

    Option currentSelection;
    Lawn lawn;

protected:
    Option getCurrentSelection() const;
};

#endif // CLI_HPP