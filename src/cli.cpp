#include "../include/cli.hpp"
#include "../tetra/time.hpp"
#include "../tetra/array.hpp"
#include <iostream>
#include <conio.h> // For _getch()

using namespace te;

CLI::CLI(Game& gameInstance) : game(gameInstance), sun(0), uiRunning(true), navigator(0, 1),
    currentSelection(OPTION_PLANT1), navigatingLawn(false) {
    uiThread = std::thread(&CLI::updateUI, this);
}

CLI::~CLI() {
    uiRunning = false;
    if (uiThread.joinable()) {
        uiThread.join();
    }
}

void CLI::updateUI() {
    while (uiRunning) {
        printInterface();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

int CLI::digits(int sun) {
    return std::to_string(sun).length();
}

void CLI::printInterface() {
    // Dealing with sun
    std::ostringstream sunstream;
    sun = game.getSun();

    str padding(12 - digits(sun), ' ');
    sunstream << "\r" << "  Sun: " << sun << padding;
    str displaySun = sunstream.str();

    // Getting Option components
    str plant1 = getOption(currentSelection, OPTION_PLANT1, "Sunflower");
    str plant2 = getOption(currentSelection, OPTION_PLANT2, "Escape Root");
    str plant3 = getOption(currentSelection, OPTION_PLANT3, "Peashooter");
    str plant4 = getOption(currentSelection, OPTION_PLANT4, "Cherry Bomb");
    str plant5 = getOption(currentSelection, OPTION_PLANT5, "Wall-nut");

    str swapOption   = getOption(currentSelection, 
                                 OPTION_SWAP_ESCAPE_ROOT,
                                 "Swap Escape Root");

    str shovelOption = getOption(currentSelection, OPTION_SHOVEL, "Shovel");
    str exitOption   = getOption(currentSelection, OPTION_EXIT, "Exit");

    // Getting Lawn components
    str lane1 = getLane(0, navigator);
    str lane2 = getLane(1, navigator);
    str lane3 = getLane(2, navigator);
    str lane4 = getLane(3, navigator);
    str lane5 = getLane(4, navigator);

    // Misc String components
    static const str BLANK(19, ' ');
    static const str LINE_SEPARATOR = "--+---+---+---+---+---+---+---+---+---+";

    // Building an interface using the collected components
    std::ostringstream interface;

    interface << RESET_TERMINAL;

    interface << displaySun   << LINE_SEPARATOR << "\n";
    interface << plant1       << lane1;
    interface << plant2       << LINE_SEPARATOR << "\n";
    interface << plant3       << lane2;
    interface << plant4       << LINE_SEPARATOR << "\n";
    interface << plant5       << lane3;
    interface << BLANK        << LINE_SEPARATOR << "\n";
    interface << BLANK        << lane4;
    interface << swapOption   << LINE_SEPARATOR << "\n";
    interface << shovelOption << lane5;
    interface << exitOption   << LINE_SEPARATOR << "\n";

    // Putting the UI in the buffer to be outputted
    buffer = interface.str();

    if (buffer != previousBuffer) {
        cout << buffer;
        previousBuffer = buffer;
    }
}

str CLI::getOption(Option currentSelection,
                   Option givenOption,
                   ref<str> plantName) {
    // Define adaptive cursor and text color
    str cursor = "> ";
    str color;
    switch (givenOption) {
        case OPTION_PLANT1: // Sunflower
            color = YELLOW;
            break;
        case OPTION_PLANT2: // Escape Root
        case OPTION_SWAP_ESCAPE_ROOT:
            color = REDDISH_BROWN;
            break;
        case OPTION_PLANT3: // Peashooter
            color = GREEN;
            break;
        case OPTION_PLANT4: // Cherry Bomb
            color = RED;
            break;
        case OPTION_PLANT5: // Wall-Nut
            color = BROWN;
            break;
        case OPTION_SHOVEL:
            color = GRAY;
            break;
        default:
            color = RESET_COLOR; // Default color
            break;
    }
    // Normalize the options that aren't selected
    if (currentSelection != givenOption) {
        cursor = "  ";
        color = RESET_COLOR;
    }
    str adaptiveBlank(17 - plantName.length(), ' ');

    std::ostringstream option;

    option << cursor << color << plantName << adaptiveBlank << RESET_COLOR;

    return option.str();
}

str CLI::getLane(int laneIndex, Coordinate& navigator) {
    // Define lane component
    std::ostringstream lane;

    for (int tileIndex : game.getLawn().tileIndices(laneIndex)) {
        str symbol = game.getLawn().getSymbol(Coordinate(laneIndex, tileIndex));
        str color = RESET_COLOR;
        // Logic for the Navigator ("o") Symbol and its colors
        if (navigatingLawn) {
            if (laneIndex == navigator.lane && tileIndex == navigator.tile) {
                if (symbol != " ") {
                    color = RED;
                }
                symbol = "o";
            }
        }

        lane << color << symbol << RESET_COLOR << " | ";
    }
    lane << "\n";

    return lane.str();
}


void CLI::navigateLawn(Option action) { 
    navigatingLawn = true;

    while (navigatingLawn) {
        printInterface();

        int ch = _getch();
        if (ch == ARROW_PREFIX) {
            switch (_getch()) {
                case UP_ARROW:
                    navigator = navigator.up();
                    break;
                case DOWN_ARROW:
                    navigator = navigator.down();
                    break;
                case LEFT_ARROW:
                    navigator = navigator.left();
                    break;
                case RIGHT_ARROW:
                    navigator = navigator.right();
                    break;
            }
        } else if (ch == ENTER_KEY) {
            switch (action) {
                case OPTION_PLANT1:
                    plant(navigator, "S");
                    break;
                case OPTION_PLANT2:
                    plant(navigator, "E");
                    break;
                case OPTION_PLANT3:
                    plant(navigator, "P");
                    break;
                case OPTION_PLANT4:
                    plant(navigator, "C");
                    break;
                case OPTION_PLANT5:
                    plant(navigator, "W");
                    break;
                case OPTION_SWAP_ESCAPE_ROOT:
                    swapEscapeRoot(navigator);
                    break;
                case OPTION_SHOVEL:
                    shovel(navigator);
                    break;
            }
        } else if (ch == ESCAPE_KEY) {
            navigatingLawn = false; // Exit the navigation loop
        }
    }
}

void CLI::plant(Coordinate& navigator, ref<str> symbol) {
    printInterface();

    if (game.getLawn().getSymbol(navigator) != " ") {
        cout << "Cannot plant on a non-blank symbol.\n";
        Time::sleep(0.25);
    } else {
        game.getLawn().replace(navigator, symbol);
        printInterface();
    }
}

void CLI::shovel(Coordinate& navigator) {
    printInterface();

    str symbol = game.getLawn().getSymbol(navigator);
    if (symbol == " ") {
        cout << "Nothing to shovel at this spot.\n";
        Time::sleep(0.25);
    } else if (symbol == "M") {
        cout << "Cannot shovel the lawn mower at this spot.\n";
        Time::sleep(0.25);
    } else {
        lawn.replace(navigator, " "); // Remove the symbol
        printInterface();
    }
}

void CLI::swapEscapeRoot(Coordinate& navigator) {
    Coordinate target = navigator; // Start target as the current position
    Coordinate originalNavigator = navigator; // Store the original navigator position
    bool running = true;

    while (running) {
        printInterface();

        if (game.getLawn().getSymbol(originalNavigator) != "E") {
            cout << "No Escape Root at the current position.\n";
            Time::sleep(0.25);
            break;
        }

        int ch = _getch();
        if (ch == ARROW_PREFIX) {
            switch (_getch()) {
                case UP_ARROW:
                    target = target.up();
                    break;
                case DOWN_ARROW:
                    target = target.down();
                    break;
                case LEFT_ARROW:
                    target = target.left();
                    break;
                case RIGHT_ARROW:
                    target = target.right();
                    break;
            }
            navigator = target; // Move navigator to the target position 
        } else if (ch == ENTER_KEY) {
            // Perform the swap operation
            if (game.getLawn().getSymbol(originalNavigator) != "E") {
                cout << "No Escape Root at the current position.\n";
                Time::sleep(0.25);

            } else if (game.getLawn().getSymbol(target) == "M") {
                cout << "Cannot swap with the lawn mower.\n";
                Time::sleep(0.25);

            } else {
                game.getLawn().swap(originalNavigator, target);
                printInterface();
            }
            running = false; // Exit the loop after swapping
        } else if (ch == ESCAPE_KEY) {
            running = false; // Exit the loop without swapping
        }
    }
}

void CLI::run() {
    std::random_device rd;
    std::mt19937 rng(rd());

    // Summon zombies at random intervals or events
    game.summonZombie(rng);
    game.summonZombie(rng);
    bool running = true;

    while (running) {
        printInterface();

        int ch = _getch();
        if (ch == ARROW_PREFIX) {
            switch (_getch()) {
                case UP_ARROW:
                    currentSelection = static_cast<Option>(
                        (currentSelection - 1 + OPTION_COUNT) % OPTION_COUNT);
                    break;
                case DOWN_ARROW:
                    currentSelection = static_cast<Option>(
                        (currentSelection + 1) % OPTION_COUNT);
                    break;
            }
        } else if (ch == ENTER_KEY) {
            // Execute the selected option
            switch (currentSelection) {
                default:
                    navigateLawn(currentSelection);
                    break;
                case OPTION_EXIT:
                    running = false;
                    break;
            }
        }
    }
}

CLI::Option CLI::getCurrentSelection() const {
    return currentSelection;
}