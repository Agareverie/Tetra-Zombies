#ifndef TETRA_BASE_HPP
#define TETRA_BASE_HPP

#include <iostream>
#include <string>

namespace te {
    using str = std::string;
    using std::cout;
    using std::endl;

    template<typename T>
    using ref = const T&;

    inline void print(const str& value) {
        std::cout << value << std::endl;
    }
}

#endif // TETRA_BASE_HPP