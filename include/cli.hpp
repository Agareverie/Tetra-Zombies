#ifndef CLI_HPP
#define CLI_HPP

#include "game.hpp"
#include <conio.h> // For _getch()

using namespace te;

class CLI {
public:

    CLI(Game& gameInstance);

    virtual ~CLI();

    int sun;
    std::thread uiThread;
    std::atomic<bool> uiRunning;
    bool navigatingLawn;
    str buffer;
    str previousBuffer; // Previous buffer to check for changes

    void run(); // Start the CLI interface
private:
    // Define keyboard keys as constants
    static const int ARROW_PREFIX = 224;
    static const int UP_ARROW = 72;
    static const int DOWN_ARROW = 80;
    static const int LEFT_ARROW = 75;
    static const int RIGHT_ARROW = 77;
    static const int ENTER_KEY = 13;
    static const int ESCAPE_KEY = 27;
    // Define constants for ANSI escape codes;
    const str RESET_TERMINAL = "\033[2J\033[1;1H";
    const str RESET_COLOR   = "\033[0m";
    const str YELLOW        = "\033[38;2;255;255;0m";
    const str REDDISH_BROWN = "\033[38;2;255;69;19m";
    const str GREEN         = "\033[38;2;0;255;0m";
    const str RED           = "\033[38;2;255;0;0m";
    const str BROWN         = "\033[38;2;139;69;19m";
    const str GRAY          = "\033[38;2;128;128;128m";

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

    Game& game;

    // Functions to render components
    int digits(int sun);
    str getOption(Option currentSelection, Option givenOption, ref<str> plantName);
    str getLane(int laneIndex, Coordinate& navigator);

    // Functions to display components
    void printInterface();
    void updateUI();

    void navigateLawn(Option action);

    void plant(Coordinate& navigator, ref<str> symbol);
    void swapEscapeRoot(Coordinate& navigator);
    void shovel(Coordinate& navigator);

    Option currentSelection;
    Coordinate navigator;
    Lawn lawn;

protected:
    Option getCurrentSelection() const;
};

#endif // CLI_HPP