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

// class ExtendedGame : public Game {
// public:
//     void cherryBombExplodes() {
//         const Coordinate coord = getLawn().getCoordinates("C");

//         std::cout << "CHA-BOOF!!" << std::endl; 
        
//         Array<Coordinate> aroundArea = {
//             coord.up().left(), coord.up(), coord.up().right(),
//             coord.left(), coord, coord.right(),
//             coord.down().left(), coord.down(), coord.down().right()
//         };

//         for (ref<Coordinate> coord : aroundArea) { 
//             getLawn().replace(coord, " ");
//         }

//         getLawn().print();
//     }

//     void run() {
//         start();
        
//         Coordinate coord = Coordinate(1, 3);
//         place(coord, "Z");
//         place(coord.up().right(), "Z");
//         place(coord.down().right().right(), "Z");
//         place(coord.down().down().right().right(), "Z");
//         swap(coord, coord.down());
//         trail(coord.down(), coord.down().left());

//         place(coord.down().right(), "C");
//         cherryBombExplodes();
//     }
// };

int main() {
    Time time;
    auto start_time = time.time();

    time.sleep(1);

    CLI cli;

    cli.run();

    auto end_time = time.time();
    time.print(start_time, end_time);
    
    return 0;
}
