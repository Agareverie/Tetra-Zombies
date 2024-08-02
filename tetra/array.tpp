#include "array.hpp"
#include <iostream>

namespace te {
    template<typename T>
    void print(const Array<T>& vec) {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i];
            if (i != vec.size() - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }

    template <typename T>
    Array<int> indices(const Array<T>& v) {
        Array<int> idx(v.size());
        for (size_t i = 0; i < v.size(); ++i) {
            idx[i] = i;
        }
        return idx;
    }

    template<typename Func, typename T>
    Array<typename std::result_of<Func(T)>::type> map(const Func& func, const Array<T>& input) {
        Array<typename std::result_of<Func(T)>::type> result;
        result.reserve(input.size());
        for (const auto& item : input) {
            result.push_back(func(item));
        }
        return result;
    }

    template<typename Func, typename T>
    Array<T> filter(const Func& func, const Array<T>& input) {
        Array<T> result;
        for (const auto& item : input) {
            if (func(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
}