#ifndef TETRA_OPTIONAL_HPP
#define TETRA_OPTIONAL_HPP

#include <optional>
#include <iostream>

namespace te {
    template<typename T>
    using optional = std::optional<T>;

    const auto None = std::nullopt;

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const optional<T>& opt) {
        if (opt.has_value()) {
            os << *opt;
        } else {
            os << "None";
        }
        return os;
    }
}

#endif // TETRA_OPTIONAL_HPP