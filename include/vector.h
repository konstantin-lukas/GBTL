//
// Created by Konstantin on 2022/11/24.
//

#pragma once
#include <iostream>

namespace gbtl {

    template<typename T>
    concept has_arithmetic_operators_no_mod = requires (T a) {
        { a + a } -> std::convertible_to<T>;
        { a - a } -> std::convertible_to<T>;
        { a * a } -> std::convertible_to<T>;
        { a / a } -> std::convertible_to<T>;
    };

    template<has_arithmetic_operators_no_mod T, size_t length>
    class vector {
    private:
        size_t m_Size;
        T ma_Components[length];
    public:
        vector() = default;
    };

}