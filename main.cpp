#include "tetra/base.hpp"
#include "tetra/array.hpp"
#include "tetra/optional.hpp"
#include "tetra/time.hpp"

#include "coordinate.hpp"
#include "lane.hpp"
#include "lawn.hpp"
#include "game.hpp"
#include "cli.hpp"

using namespace te;

int main() {
    Time time;
    auto start_time = time.time();
    
    Game game;

    // Pass the Game instance to CLI

    CLI cli(game);

    cli.run();

    auto end_time = time.time();
    time.print(start_time, end_time);
    
    return 0;
}
