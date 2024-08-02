#ifndef TETRA_ARRAY_HPP
#define TETRA_ARRAY_HPP

#include <vector>

namespace te {
    template<typename T>
    using Array = std::vector<T>;

    template<typename T>
    void print(const Array<T>& vec);

    template <typename T>
    Array<int> indices(const Array<T>& v);

    template<typename Func, typename T>
    Array<typename std::result_of<Func(T)>::type> map(const Func& func, const Array<T>& input);

    template<typename Func, typename T>
    Array<T> filter(const Func& func, const Array<T>& input);
}

#include "array.tpp"

#endif // TETRA_ARRAY_HPP