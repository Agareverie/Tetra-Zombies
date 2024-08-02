#include "../include/cli.hpp"
#include "../tetra/time.hpp"
#include "../tetra/array.hpp"
#include <iostream>
#include <conio.h> // For _getch()

using namespace te;

CLI::CLI() : Game(), sun(0), uiRunning(true),
    currentSelection(OPTION_PLANT1), lawn() {
    uiThread = std::thread(&CLI::updateUI, this);
}

CLI::~CLI() {
    uiRunning = false;
    if (uiThread.joinable()) {
        uiThread.join();
    }
}

void CLI::clearScreen() {
    std::cout << "\033[2J\033[1;1H" << std::flush;
    std::cout << "\033[3J" << std::flush;
}

void CLI::resetUI() {
    clearScreen();
    printInterface();
}

void CLI::updateUI() {
    currentSelection = getCurrentSelection();
    while (uiRunning) {
        Time::sleep(0.001);
        resetUI();
        Time::sleep(4.999);
    }
}

void CLI::printInterface() {
    int sun = getSun();
    str adaptiveBlank;

    if (sun >= 100) { 
        adaptiveBlank = "         "; 
    } else if (sun >= 10) {
        adaptiveBlank = "          "; 
    } else {
        adaptiveBlank = "           " ; 
    }
    clearScreen();
    //   Sun: 150         --+---+---+---+---+---+---+---+---+---+
    cout << "  Sun: " << sun << adaptiveBlank;
    lawn.lineSeparator();

    // > Sunflower        M | S |   | P |   |   |   |   |   |   |
    printMenuOption(currentSelection, OPTION_PLANT1,
        "Sunflower        ");
    printLawnRow(0);

    //   Escape Root      --+---+---+---+---+---+---+---+---+---+
    printMenuOption(currentSelection, OPTION_PLANT2, 
        "Escape Root      ");
    lawn.lineSeparator();

    //   Peashooter       M | S |   | P |   |   |   |   |   |   |
    printMenuOption(currentSelection, OPTION_PLANT3, 
        "Peashooter       ");
    printLawnRow(1);

    //   Cherry Bomb      --+---+---+---+---+---+---+---+---+---+
    printMenuOption(currentSelection, OPTION_PLANT4, 
        "Cherry Bomb      ");
    lawn.lineSeparator();

    //   Wall-Nut         M |   |   | P |   |   |   |   |   |   |
    printMenuOption(currentSelection, OPTION_PLANT5, 
        "Wall-Nut         ");
    printLawnRow(2);

    //                    --+---+---+---+---+---+---+---+---+---+
    cout << "                   "; // Blank Space
    lawn.lineSeparator();

    //                    M | S |   |   |   |   |   |   |   |   |
    cout << "                   "; // Blank Space
    printLawnRow(3);

    //   Swap Escape Root --+---+---+---+---+---+---+---+---+---+
    printMenuOption(currentSelection, OPTION_SWAP_ESCAPE_ROOT, 
        "Swap Escape Root ");
    lawn.lineSeparator();

    //   Shovel           M |   |   |   |   |   |   |   |   |   |
    printMenuOption(currentSelection, OPTION_SHOVEL, 
        "Shovel           ");
    printLawnRow(4);

    //   Exit             --+---+---+---+---+---+---+---+---+---+
    printMenuOption(currentSelection, OPTION_EXIT, 
        "Exit             ");
    lawn.lineSeparator();
} 
/* Output:
  Sun: 150         --+---+---+---+---+---+---+---+---+---+
  Sunflower        M | S |   | P |   |   |   |   |   |   |
  Escape Root      --+---+---+---+---+---+---+---+---+---+
  Peashooter       M | S |   | P |   |   |   |   |   |   |
  Cherry Bomb      --+---+---+---+---+---+---+---+---+---+
  Wall-Nut         M |   |   | P |   |   |   |   |   |   |
                   --+---+---+---+---+---+---+---+---+---+
                   M | S |   |   |   |   |   |   |   |   |
  Swap Escape Root --+---+---+---+---+---+---+---+---+---+
  Shovel           M |   |   |   |   |   |   |   |   |   |
> Exit             --+---+---+---+---+---+---+---+---+---+
*/

void CLI::printMenuOption(Option currentSelection,
                          Option givenOption, ref<str> text) {
    cout << (currentSelection == givenOption ? "> " : "  ") << text;
}

void CLI::printLawnRow(int laneIndex) {
    for (int tileIndex : lawn.tileIndices(laneIndex)) {
        cout << lawn.getSymbol(Coordinate(laneIndex, tileIndex)) << " | ";
    }
    cout << "\n";
}



void CLI::navigateLawn(Option action) {
    Coordinate navigator(0, 1);
    bool running = true;

    while (running) {
        clearScreen();
        lawn.printWithNavigator(navigator);
        cout << "Current action: ";

        switch (action) {
            case OPTION_PLANT1:
                cout << "Plant Sunflower (\"S\")\n";
                break;
            case OPTION_PLANT2:
                cout << "Plant Escape Root (\"E\")\n";
                break;
            case OPTION_PLANT3:
                cout << "Plant Peashooter (\"P\")\n";
                break;
            case OPTION_PLANT4:
                cout << "Plant Cherry Bomb (\"C\")\n";
                break;
            case OPTION_PLANT5:
                cout << "Plant Wall-nut (\"W\")\n";
                break;
            case OPTION_SWAP_ESCAPE_ROOT:
                std::cout << "Swap Escape Root\n";
                break;
            case OPTION_SHOVEL:
                cout << "Shovel\n";
                break;
            default:
                cout << "Navigate Lawn\n";
                break;
        }

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
                // case OPTION_NAVIGATE_LAWN:
                //     cout << "Navigate Lawn selected."
                //          << " Use arrow keys to move. Press Esc to exit.\n";
                //     break;
            }
        } else if (ch == ESCAPE_KEY) {
            running = false; // Exit the navigation loop
        }
    }
}

void CLI::plant(Coordinate& navigator, ref<str> symbol) {
    clearScreen();
    lawn.printWithNavigator(navigator);
    std::cout << "Planting (\"" << symbol << "\") at ";
    navigator.print();
    std::cout << std::endl;

    if (lawn.getSymbol(navigator) != " ") {
        std::cout << "Cannot plant on a non-blank symbol.\n";
    } else {
        place(lawn, navigator, symbol); // Place "E" at the selected coordinate
    }
    Time::sleep(0.25);
}

void CLI::shovel(Coordinate& navigator) {
    clearScreen();
    lawn.printWithNavigator(navigator);
    cout << "Shoveling at ";
    navigator.print();
    cout << endl;

    str symbol = lawn.getSymbol(navigator);
    if (symbol == " ") {
        cout << "Nothing to shovel at this spot.\n";
    } else if (symbol == "M") {
        cout << "Cannot shovel the lawn mower at this spot.\n";
    } else {
        shovelTile(lawn, navigator); // Remove the symbol
    }
    Time::sleep(0.25);
}

void CLI::swapEscapeRoot(Coordinate& navigator) {
    Coordinate target = navigator; // Start target as the current position
    Coordinate originalNavigator = navigator; // Store the original navigator position
    bool running = true;

    while (running) {
        clearScreen();
        lawn.printWithNavigator(navigator);

        if (lawn.getSymbol(originalNavigator) != "E") {
            cout << "No Escape Root at the current position.\n";
            Time::sleep(0.25);
            break;
        }

        cout << "Swapping Escape Root (\"E\") at ";
        originalNavigator.print();
        cout << " with position ";
        target.print();

        cout << ".\nUse arrow keys to move the target.\n";
        cout << "Press Enter to swap or Esc to cancel.\n";

        

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
            if (lawn.getSymbol(originalNavigator) != "E") {
                cout << "No Escape Root at the current position.\n";

            } else if (lawn.getSymbol(target) == "M") {
                cout << "Cannot swap with the lawn mower.\n";

            } else {
                swap(lawn, originalNavigator, target);
            }
            Time::sleep(0.25);
            running = false; // Exit the loop after swapping
        } else if (ch == ESCAPE_KEY) {
            running = false; // Exit the loop without swapping
        }
    }
}

void CLI::run() {
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
                case OPTION_PLANT1:
                case OPTION_PLANT2:
                case OPTION_PLANT3:
                case OPTION_PLANT4:
                case OPTION_PLANT5:
                case OPTION_SWAP_ESCAPE_ROOT:
                case OPTION_SHOVEL:
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